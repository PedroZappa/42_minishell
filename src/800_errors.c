/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   800_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:35:23 by passunca          #+#    #+#             */
/*   Updated: 2024/06/22 10:26:18 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup error Error functions
* @{
*
* @brief		Error functions
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			Error printing
/// @param msg		Message to be printed
/// @param status	Error number
/// @return			SUCCESS(1)
/// @details		Prints message to stderr
///					- Saves exit code to g_exit
/// @note			Used all over the code base
int	ft_err(char *msg, int status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	g_exit = status;
	return (FAILURE);
}

/* @} */
