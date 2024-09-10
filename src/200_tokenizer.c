/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:44:44 by passunca          #+#    #+#             */
/*   Updated: 2024/09/09 09:16:42 by passunca         ###   ########.fr       */
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

static int		ft_get_tkns(t_shell *sh, char *line, \
						t_token **tks, t_tk_ops *ops);
static t_tk_ops	ft_get_tk(char *tk, t_tk_ops *ops);

/// @brief			Tokenizer
/// @param sh		Pointer to a t_shell struct
/// @param line		Line buffer
/// @param tks		Pointer to a t_token struct
/// @return			SUCCESS(0)
///	@return			FAILURE(errno)
///	@note			Used in ft_parser()
int	ft_tokenizer(t_shell *sh, char *line, t_token **tks)
{
	t_tk_ops	ops[19];
	t_token		*tk;

	ft_init_ops(ops);
	if (ft_get_tkns(sh, line, tks, ops) != SUCCESS)
		return (ft_err(TKNZR_ERR, errno));
	tk = *tks;
	while (tk)
	{
		if (tk->type == TK_HEREDOC && tk->next != NULL
			&& tk->next->type == TK_CMD)
		{
			tk->next->name = ft_heredoc_expander(sh, tk->next->name);
			tk = tk->next->next;
			continue ;
		}
		if (tk->type != TK_BLANK)
			tk->name = ft_expander(sh, tk->name);
		tk = tk->next;
	}
	return (SUCCESS);
}

/// @brief			Get tokens from line
/// @param tks		Pointer to a t_token struct
/// @param line		Line buffer
/// @return			SUCCESS(0) on success,
///					FAILURE(1) on failure
///	@note			Used in ft_tokenizer()
static int	ft_get_tkns(t_shell *sh, char *line, t_token **tks, t_tk_ops *ops)
{
	char		*tmp;
	t_tk_ops	tk;

	tmp = line;
	while (line && line[0])
	{
		tk = ft_get_tk(line, ops);
		if (tk.tkn == NO_TOKEN)
		{
			line++;
			continue ;
		}
		line += tk.len;
		ft_home_expand(sh, &tk);
		if (tk.type != TK_BLANK)
			ft_tk_add_free(tks, ft_tk_new(tk.tkn, tk.type,
					(int)ft_strlen(tk.tkn)), &tk);
		tmp = line;
	}
	if (tmp != line)
		ft_tk_add_free(tks, ft_tk_new(tmp, TK_CMD, (line - tmp)), &tk);
	return (SUCCESS);
}

static t_tk_ops	ft_find_ops(char *tk, t_tk_ops *ops)
{
	int		i;
	int		j;
	char	dq;

	i = 0;
	dq = (tk[i] == '\"') * '\"' + (tk[i] == '\'') * '\'';
	while (tk[i])
	{
		j = -1;
		while ((ops != NULL) && (ops[++j].tkn != NULL) && (dq == 0))
		{
			if (ops[j].tkn == NULL || (tk[i] != ops[j].tkn[0]))
				continue ;
			if (i != 0)
				return ((t_tk_ops){ft_substr(tk, 0, (size_t)i),
					TK_CMD, i});
			if (ft_strnstr(tk, ops[j].tkn, INT_MAX) != NULL)
				return ((t_tk_ops){ft_strdup(ops[j].tkn),
					ops[j].type, (size_t)ops[j].len});
		}
		i++;
		dq = ft_get_dq(dq, tk[i]);
	}
	return ((t_tk_ops){ft_substr(tk, 0, (size_t)i), TK_CMD, i});
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
	int			i;

	i = 0;
	while (ft_isspace(tk[i]))
		i++;
	if (i > 0)
		return ((t_tk_ops){"", TK_BLANK, i});
	return (ft_find_ops(tk, ops));
}

/** @} */
