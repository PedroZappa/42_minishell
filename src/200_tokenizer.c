/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:44:44 by passunca          #+#    #+#             */
/*   Updated: 2024/07/08 20:08:38 by passunca         ###   ########.fr       */
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

static void		ft_init_ops(t_tk_ops *ops);
static int		ft_get_tkns(t_shell *sh, char *line, \
						t_token **tks, t_tk_ops *ops);
static t_tk_ops	ft_get_tk(char *tk, t_tk_ops *ops);
// static int		ft_has_match(char **line);

/// @brief			Tokenizer
/// @details
/// - Initializes t_tk_ops array with all supported tokens
/// - Get tokens from line
/// - Handle Token Expansion
/// 	- Expand ~ (HOME)
/// 	- Expand all other tokens
/// @param sh		Pointer to a t_shell struct
/// @param line		Line buffer
/// @param tks		Pointer to a t_token struct
/// @return			SUCCESS(0)
///	@return			FAILURE(errno)
///	@note			Used in ft_parser()
int	ft_tokenizer(t_shell *sh, char *line, t_token **tks)
{
	t_tk_ops	ops[17];
	t_token		*tk;

	ft_init_ops(ops);
	if (ft_get_tkns(sh, line, tks, ops) != SUCCESS)
		return (ft_err(TKNZR_ERR, errno));
	tk = *tks;
	while (tk)
	{
		tk->name = ft_expander(sh, tk->name);
		tk = tk->next;
	}
	return (SUCCESS);
}

/// @brief			Initialize t_tk_ops array with all supported tokens
/// @param ops		Pointer to an array of t_tk_ops structs
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
	ops[15] = (t_tk_ops){"*", TK_WILD, 1};
	ops[16] = (t_tk_ops){NULL, 0, 0};
}

/// @brief			Get tokens from line
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
/// @param tks		Pointer to a t_token struct
/// @param line		Line buffer
/// @return			SUCCESS(0) on success,
///					FAILURE(1) on failure
///	@note			Used in ft_tokenizer()
static int	ft_get_tkns(t_shell *sh, char *line, t_token **tks, t_tk_ops *ops)
{
	char		*tkn_str;
	char		*tmp;
	t_tk_ops	tk;

	tmp = line;
	while (line && *line)
	{
		tk = ft_get_tk(line, ops);
		if (tk.tkn != NO_TOKEN)
		{
			line += tk.len;
			tkn_str = ft_strdup(tk.tkn);
			if ((tkn_str[0] == '~') && sh->home)
			{
				ft_free(tk.tkn);
				if (tkn_str[1] == '/')
					tk.tkn = ft_strjoin(sh->home, "/");
				else
					tk.tkn = ft_strdup(sh->home);
			}
			ft_free(tkn_str);
			if ((tk.type != TK_BLANK) && (tk.tkn[0] != '~'))
				ft_tk_add_free(tks, ft_tk_new(tk.tkn, tk.type, (int)ft_strlen(tk.tkn)), &tk);
			tmp = line;
		}
		else
			++line;
	}
	if (tmp != line)
		ft_tk_add_free(tks, ft_tk_new(tmp, TK_CMD, (line - tmp)), &tk);
	return (SUCCESS);
}

/// @brief			Find matching token operation
/// @details
///	- Compares tk with each token in the array
/// @param tk		Token string
/// @return			SUCCESS(t_tk_ops struct with op data)
///					FAILURE(empty t_tk_ops struct)
/// @note			Used in ft_get_tkns()
static t_tk_ops	ft_get_tk(char *tk, t_tk_ops *ops)
{
	t_tk_ops	ret;
	int			i;

	ret = (t_tk_ops){NULL, TK_CMD, 0};
	i = 0;
	if (!ft_isspace(tk[0]))
	{
		if (tk[0] == '\"')
		{
			++i;
			while (tk[i] && (tk[i] != '\"'))
				++i;
			if (tk[i] == '\"')
				++i;
			ret = (t_tk_ops){ft_substr(tk, 0, (size_t)i), TK_CMD, i};
			return (ret);
		}
		if (tk[0] == '\'')
		{
			++i;
			while (tk[i] && (tk[i] != '\''))
				++i;
			if (tk[i] == '\'')
				++i;
			ret = (t_tk_ops){ft_substr(tk, 0, (size_t)i), TK_CMD, i};
			return (ret);
		}
		while (tk[i] && !ft_isspace(tk[i]) && (tk[i] != '\'') && (tk[i] != '\"'))
			++i;
		ret = (t_tk_ops){ft_substr(tk, 0, (size_t)i), TK_CMD, i};
	}
	else
		ret = (t_tk_ops){"", TK_BLANK, 1};
	i = 0;
	while ((&ops[i] != NULL) && (ops[i].tkn != NULL))
	{
		if (!ft_strncmp(tk, ops[i].tkn, (size_t)ops[i].len))
		{
			ret.type = ops[i].type;
			return (ret);
		}
		++i;
	}
	return (ret);
}

/// @brief			Check if line contains a matching closing quote
/// @details
/// - Checks if line contains a matching closing quote
/// 	- If it doesn't, move pointer to end of the line
/// @param quote	Pointer to a quote
/// @return			SUCCESS(matching quote found)
///					FAILURE(no match)
/// @note			Used in ft_get_tkns() when a quote is parsed
// static int	ft_has_match(char **quote)
// {
// 	char	*line_0;
//
// 	line_0 = (*quote);
// 	(*quote) = ft_strrchr(((*quote) + 1), **quote);
// 	if (!(*quote))
// 	{
// 		(*quote) = line_0 + ft_strlen(line_0);
// 		return (FAILURE);
// 	}
// 	return (SUCCESS);
// }

/** @} */
