/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:44:44 by passunca          #+#    #+#             */
/*   Updated: 2024/06/23 17:29:17 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup tokenizer Tokenizer
* @{
*
* @brief		Tokenizer
* @version		1.0
***/

#include "../inc/minishell.h"

static int		ft_get_tkns(char *line, t_token **tks);
static t_tk_ops	ft_get_tk(char *tk);
static void		ft_init_ops(t_tk_ops *ops);
static int		ft_has_match(char **line);

/// @brief			Tokenizer
/// @param sh		Pointer to a t_shell struct
/// @param line		Line buffer
/// @param tks		Pointer to a t_token struct
/// @var tk
/// Stores the first token in the list
///	Used to traverse the tokens list
/// @return			SUCCESS(0)
///	@return			FAILURE(errno)
/// @details
/// - Get tokens from line
/// - Handle Token Expansion
/// 	- Expand ~ (HOME)
/// 	- Expand all other tokens
///	@note			Used in ft_parser()
int	ft_tokenizer(t_shell *sh, char **line, t_token **tks)
{
	t_token	*tk;
	char	*name;

	if (ft_get_tkns(*line, tks) != SUCCESS)
		return (ft_err(TKNZR_ERR, errno));
	tk = *tks;
	while (tk)
	{
		name = tk->name;
		if (name[0] == '~' && (ft_strlen(name) == 1))
			tk->name = ft_strdup(sh->home);
		else
			tk->name = ft_tk_expander(sh, name);
		tk = tk->next;
		free(name);
	}
	return (SUCCESS);
}

/// @brief			Get tokens from line
/// @param tks		Pointer to a t_token struct
/// @param line		Line buffer
/// @var tmp		Pointer to the previous token
/// @var tk			Stores extracted token from line
/// @return			SUCCESS(0) on success,
///					FAILURE(1) on failure
/// @details
/// - Stash line in tmp
/// - Loop through line
/// 	- Get token data
/// 	- If the token is part of a command, add it to tokens list
///		- If a operation token is parsed:
/// 		- Move pointer to next token
/// 		- If the token is not a blank, add it to the li	st
///		- Check if line contains a matching closing quote
/// - Get last remaining remaining token
///	@note			Used in ft_tokenizer()
static int	ft_get_tkns(char *line, t_token **tks)
{
	char		*tmp;
	t_tk_ops	tk;

	tmp = line;
	while (line && *line)
	{
		tk = ft_get_tk(line);
		if ((tk.tkn != NO_TOKEN) && (tmp != line))
			ft_tk_add(tks, ft_tk_new(tmp, TK_CMD, (line - tmp)));
		if (tk.tkn != NO_TOKEN)
		{
			line += tk.len;
			if (tk.type != TK_BLANK)
				ft_tk_add(tks, ft_tk_new(tk.tkn, tk.type, tk.len));
			tmp = line;
		}
		else if (((*line == '\'') || (*line == '\"')) && ft_has_match(&line))
			return (FAILURE);
		else
			++line;
	}
	if (tmp != line)
		ft_tk_add(tks, ft_tk_new(tmp, TK_CMD, (line - tmp)));
	ft_free(tk.tkn);
	return (SUCCESS);
}

/// @brief			Find matching token operation
/// @param tk		Token string
/// @var ops		Pointer to an array of t_tk_ops structs
/// @var ret		Pointer to a t_tk_ops struct to be returned
/// @var i			To iterate the array of supported tokens
/// @return			SUCCESS(t_tk_ops struct with op data)
///					FAILURE(empty t_tk_ops struct)
/// @details
/// - Initializes t_tk_ops array with all supported tokens
///	- Compares tk with each token in the array
/// @note			Used in ft_get_tkns()
static t_tk_ops	ft_get_tk(char *tk)
{
	t_tk_ops	ops[16];
	t_tk_ops	ret;
	int			i;

	ft_init_ops(ops);
	ret = (t_tk_ops){0, TK_CMD, 0};
	i = 0;
	if (!ft_isspace(tk[0]))
	{
		while (tk[i] && (!ft_isspace(tk[i])))
			++i;
		ret = (t_tk_ops){ft_substr(tk, 0, i), TK_CMD, i};
	}
	else
		ret = (t_tk_ops){ft_substr(tk, 0, 1), TK_BLANK, 1};
	i = -1;
	while (ops[++i].tkn)
		if (!ft_strncmp(tk, ops[i].tkn, ops[i].len))
			return (ops[i]);
	return (ret);
}

static void	ft_init_ops(t_tk_ops *ops)
{
	ops[0] = (t_tk_ops){"<<", TK_IN, 2};
	ops[1] = (t_tk_ops){"<", TK_IN, 1};
	ops[2] = (t_tk_ops){">>", TK_OUT, 2};
	ops[3] = (t_tk_ops){">|", TK_OUT, 2};
	ops[4] = (t_tk_ops){"<>", TK_OUT, 2};
	ops[5] = (t_tk_ops){">", TK_OUT, 1};
	ops[6] = (t_tk_ops){"||", TK_OR, 2};
	ops[7] = (t_tk_ops){"&&", TK_AND, 2};
	ops[8] = (t_tk_ops){"|", TK_PIPE, 1};
	ops[9] = (t_tk_ops){" ", TK_BLANK, 1};
	ops[10] = (t_tk_ops){"\n", TK_BLANK, 1};
	ops[11] = (t_tk_ops){"\v", TK_BLANK, 1};
	ops[12] = (t_tk_ops){"\t", TK_BLANK, 1};
	ops[13] = (t_tk_ops){"\r", TK_BLANK, 1};
	ops[14] = (t_tk_ops){"\f", TK_BLANK, 1};
	ops[15] = (t_tk_ops){NULL, 0, 1};
}

/// @brief			Check if line contains a matching closing quote
/// @param quote	Pointer to a quote
/// @var line_0		Pointer to store the start of the line
/// @return			SUCCESS(matching quote found)
///					FAILURE(no match)
/// @details		- Checks if line contains a matching closing quote
/// 					- If it doesn't, move pointer to end of the line
/// @note			Used in ft_get_tkns() when a quote is parsed
static int	ft_has_match(char **quote)
{
	char	*line_0;

	line_0 = (*quote);
	(*quote) = ft_strchr(((*quote) + 1), **quote);
	if (!(*quote))
	{
		(*quote) = line_0 + ft_strlen(line_0);
		return (FAILURE);
	}
	return (SUCCESS);
}

/** @} */
