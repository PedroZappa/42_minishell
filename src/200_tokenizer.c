/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:44:44 by passunca          #+#    #+#             */
/*   Updated: 2024/06/19 21:24:19 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int		ft_get_tkns(char *line, t_token **tks);
static t_tk_ops	ft_get_tk(char *tk);
static int		ft_is_tkquote(char **line);
static char		*ft_tk_expander(t_shell *sh, char *val);

/// @brief			Tokenizer
/// @param sh		Pointer to a t_shell struct
/// @param line		Line buffer
/// @param tks		Pointer to a list og t_token structs
/// @return			Return 0 on success, 1 on failure
/// @details		- Get tokens from line
///					- Handle Token Expansion
///						- Expand ~ (HOME)
///						- Expand all other tokens
int	ft_tokenizer(t_shell *sh, char **line, t_token **tks)
{
	t_token	*tk_ptr;
	char	*val;

	if (ft_get_tkns(*line, tks) != SUCCESS)
		return (ft_err(TKNZR_ERR, errno));
	tk_ptr = *tks;
	while (tk_ptr)
	{
		val = tk_ptr->val;
		if (val[0] == '~' && (ft_strlen(val) == 1))
			tk_ptr->val = ft_strdup(sh->home);
		else
			tk_ptr->val = ft_tk_expander(sh, val);
		tk_ptr = tk_ptr->next;
		free(val);
	}
	return (SUCCESS);
}

/// @brief			Get tokens from line
/// @param line		Line buffer
/// @param tks		Pointer to a t_token struct
/// @return			Return 0 on success, errno on failure
/// @details		- Loop through line
///						- Call ft_get_tk() to get token operation
/// 			   		- Add token to list
///				   		- Check if line contains a matching closing quote
///	@note			Used in ft_tokenizer()
static int	ft_get_tkns(char *line, t_token **tks)
{
	t_tk_ops	tk_ptr;
	char		*tmp;

	tmp = line;
	while (line && *line)
	{
		tk_ptr = ft_get_tk(line);
		if (tk_ptr.tkn != 0)
		{
			line += tk_ptr.len;
			ft_tk_add(tks, ft_tk_new(tk_ptr.tkn, tk_ptr.type, tk_ptr.len));
		}
		else if (ft_is_tkquote(&line) && ((*line == '\'') || (*line == '\"')))
			return (ft_err(TKNZR_ERR, errno));
		else
			++line;
	}
	return (SUCCESS);
}

/// @brief			Find matching token operation
/// @param tk		Token string
/// @return			t_tk_ops struct
/// @details		- Iniitializes t_tk_ops array with all supported tokens
///					- Compares tk with each token in the array
///					- Re
/// @note			Used in ft_get_tkns()
static t_tk_ops	ft_get_tk(char *tk)
{
	t_tk_ops	ops[16];
	t_tk_ops	curr_op;
	int			i;

	ops[0] = (t_tk_ops){"<<", TK_IN, 2};
	ops[1] = (t_tk_ops){"<", TK_IN, 1};
	ops[2] = (t_tk_ops){">>", TK_OUT, 2};
	ops[3] = (t_tk_ops){">|", TK_OUT, 2};
	ops[4] = (t_tk_ops){"<>", TK_OUT, 2};
	ops[5] = (t_tk_ops){">", TK_OUT, 1};
	ops[6] = (t_tk_ops){" ", TK_BLANK, 1};
	ops[7] = (t_tk_ops){"\n", TK_BLANK, 1};
	ops[8] = (t_tk_ops){"\v", TK_BLANK, 1};
	ops[9] = (t_tk_ops){"\t", TK_BLANK, 1};
	ops[10] = (t_tk_ops){"\r", TK_BLANK, 1};
	ops[11] = (t_tk_ops){"\f", TK_BLANK, 1};
	ops[12] = (t_tk_ops){"||", TK_OR, 2};
	ops[13] = (t_tk_ops){"&&", TK_AND, 2};
	ops[14] = (t_tk_ops){"|", TK_PIPE, 1};
	ops[15] = (t_tk_ops){NULL, 0, 1};
	curr_op = (t_tk_ops){0, 0, 0};
	i = -1;
	while (ops[++i].tkn)
		if (!ft_strncmp(tk, ops[i].tkn, ops[i].len))
			return (ops[i]);
	return (curr_op);
}

/// @brief			Check if line contains a matching closing quote
/// @param line		Line buffer
/// @var line_0		Pointer to store the start of the line
/// @return			0 on success, 1 on failure
/// @details		Used to check a line for a matching closing quote
/// @note			Used in ft_get_tkns() when a quote is parsed
static int	ft_is_tkquote(char **line)
{
	char	*line_0;

	line_0 = (*line);
	(*line) = ft_strchr(((*line) + 1), **line);
	if (!(*line))
	{
		(*line) = line_0 + ft_strlen(line_0);
		return (FAILURE);
	}
	return (SUCCESS);
}

static char	*ft_tk_expander(t_shell *sh, char *val)
{
	(void)sh;
	(void)val;
	return (NULL);
}
