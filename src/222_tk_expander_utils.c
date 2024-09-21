/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   222_tk_expander_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:45:33 by gfragoso          #+#    #+#             */
/*   Updated: 2024/09/01 23:45:33 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup tk_expander Token expander
* @{
*
* @brief		Token expander var checker
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			Token expander alpha checker
/// @param c		Character to check
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_check_alpha(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (SUCCESS);
	return (FAILURE);
}

/// @brief			Token expander alphanum checker
/// @param c		Character to check
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_check_alnum(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (SUCCESS);
	return (FAILURE);
}

/// @brief			Fill expanded variable
/// @param sh		Pointer to a t_shell struct
/// @param tkn		Token string
char	*ft_fill_var(t_shell *sh, char *tkn)
{
	char	*var;
	int		i;

	i = 1;
	var = NULL;
	if (ft_check_alnum(tkn[i]) == SUCCESS)
		var = ft_get_var((tkn + 1), sh->envp);
	else if (tkn[i] == '?')
		var = ft_itoa(g_exit);
	else
		var = ft_strdup(tkn);
	return (var);
}

/// @brief			Adds content to the end of a list
/// @param lst 		List pointer
/// @param ptr 		Content to add
void	ft_lstadd_back_ptr(t_list **lst, void *ptr)
{
	t_list	*new;

	new = ft_lstnew(ptr);
	ft_lstadd_back(lst, new);
}

/** @} */
