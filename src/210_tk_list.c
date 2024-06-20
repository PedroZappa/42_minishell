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

/// @brief			Create new token
/// @param line		Line buffer
/// @param type		Token type
/// @param len		Length of token
/// @return			Pointer to a t_token struct
/// @details		...
/// @note			Used in ft_get_tkns()
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

/// @brief			Add token to list
/// @param tk_list	Pointer to a list of t_token structs
/// @param tk		Pointer to a t_token struct
/// @var curr		Pointer to a local t_token struct
/// @details		- Get last token in list
///					-
/// @note			Used in ft_get_tkns()
void	ft_tk_add(t_token **tk_list, t_token *tk)
{
	t_token	*curr;

	if (*tk_list)
	{
		curr = ft_tk_last(*tk_list);
		(*curr).next = *tk_list;
	}
	else
		*tk_list = tk;
}

/// @brief			Get last token in list
/// @param tk		Pointer to a t_token struct
/// @return			Pointer to a t_token struct
/// @details		
/// @note			Used in ft_tk_add()
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
