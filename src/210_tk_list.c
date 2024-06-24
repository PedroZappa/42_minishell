/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   210_tk_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:34:20 by passunca          #+#    #+#             */
/*   Updated: 2024/06/24 15:47:32 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup tk_list Token list
* @{
*
* @brief		Token related functions
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			Create new token
/// @param line		Line buffer
/// @param type		Token type
/// @param len		Length of token
/// @return			SUCCESS(Pointer to a t_token struct)
///	@return			FAILURE(NULL)
/// @details
/// - Allocates memory for a t_token struct
/// - Stores line in name
/// - Stores type in type
/// - Stores len in len
/// - If first character is not a quote, set to_del to 1
/// - Set next to NULL (Sentinel value)
/// @note			Used in ft_get_tkns()
t_token	*ft_tk_new(char *line, t_token_type type, int len)
{
	t_token	*tk;

	tk = ft_calloc(1, sizeof(t_token));
	if (!tk)
		return (ft_err(TKNZR_ERR, errno), NULL);
	tk->name = ft_substr(line, 0, len);
	tk->type = type;
	tk->len = len;
	tk->to_del = 0;
	if ((tk->name[0] != '\'') || (tk->name[0] != '\"'))
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
/// @return			SUCCESS(Pointer to a t_token struct)
/// 				FAILURE(NULL)
/// @details		- Traverse list until last token is reached
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

/** @} */
