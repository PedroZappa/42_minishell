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
///
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
/// @return			Return 0 on success, 1 on failure
/// @details		- Call ft_get_tk() 
///
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
	t_tk_ops	ops[16] = {{"<<", TK_IN, 2}, {"<", TK_IN, 1}, {">>", TK_OUT, 2},
	{">|", TK_OUT, 2}, {"<>", TK_OUT, 2}, {">", TK_OUT, 1},
	{" ", TK_BLANK, 1}, {"\n", TK_BLANK, 1}, {"\v", TK_BLANK, 1},
	{"\t", TK_BLANK, 1}, {"\r", TK_BLANK, 1}, {"\f", TK_BLANK , 1},
	{"||", TK_OR, 2}, {"&&", TK_AND, 2}, {"|", TK_PIPE, 1}, {NULL, 0, 1}};
	t_tk_ops	curr_op;
	int			i;

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
