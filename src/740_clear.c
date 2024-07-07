/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   740_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:25:33 by passunca          #+#    #+#             */
/*   Updated: 2024/07/07 11:42:39 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup 	clear	clear built-in command
* @{
*
* @brief		clear screen built-in
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			clear screen built-in
/// @details
/// Clear screen ANSI sequence: "\033[H\033[J"
///		- `\033[H` : moves the cursor to the home position
///		- `\033[J` : clears the screen from the cursor to the end of the screen
/// @param n		Command index
/// @return			SUCCESS(0)
int	ft_clear(int n)
{
	(void)n;
    ft_printf("\033[H\033[J");
	return (SUCCESS);
}

/** @} */
