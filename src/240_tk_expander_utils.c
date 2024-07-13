/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   240_tk_expander_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:09:42 by passunca          #+#    #+#             */
/*   Updated: 2024/07/13 12:15:43 by passunca         ###   ########.fr       */
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
int	ft_check_alpha_c(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (SUCCESS);
	return (FAILURE);
}

/// @brief			Token expander alphanum checker
/// @param c		Character to check
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_check_alnum_c(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (SUCCESS);
	return (FAILURE);
}

/** @} */
