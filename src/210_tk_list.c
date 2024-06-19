/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   210_tk_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:34:20 by passunca          #+#    #+#             */
/*   Updated: 2024/06/19 21:04:12 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*ft_tk_new(char *line, t_token_type type, int len)
{
	t_token	*tk;

	tk = ft_calloc(1, sizeof(t_token));
	if (!tk)
		return (ft_err(TKNZR_ERR, errno), NULL);
	tk->val = ft_substr(line, 0, len);
	tk->type = type;
	tk->len = len;
	if ((tk->val[0] == '\'') || (tk->val[0] == '\"'))
		tk->to_del = 0;
	else
		tk->to_del = 1;
	tk->next = NULL;
	return (tk);
}

void	ft_tk_add(t_token **tk_list, t_token *tks)
{
	t_token	*curr;

	if (*tk_list)
	{
		curr = ft_tk_last(*tk_list);
		(*curr).next = *tk_list;
	}
	else
		*tk_list = tks;
}

t_token	*ft_tk_last(t_token *tk)
{
	if (!tk)
		return (NULL);
	while (tk->next)
	{
		if ((*tk).next == NULL)
			return (tk);
		tk = tk->next;
	}
	return (tk);
}
