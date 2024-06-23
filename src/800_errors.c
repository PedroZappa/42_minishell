/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   800_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:35:23 by passunca          #+#    #+#             */
/*   Updated: 2024/06/23 11:04:59 by passunca         ###   ########.fr       */
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
/// @details		Prints message to stderr
///					- Saves exit code to g_exit
/// @param msg		Message to be printed
/// @param status	Error number
/// @return			SUCCESS(1)
/// @note			Used all over the code base
int	ft_err(char *msg, int status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	g_exit = status;
	return (FAILURE);
}

/// @brief Create error message
/// @details
/// -
/// @param tkn		Message to be printed
/// @param err		Error number
/// @return			SUCCESS(0)
int	ft_syntax_err(char *tkn, int err)
{
	char	*start;
	char	*end;

	start = ft_strjoin("Syntax error near unexpected token'", tkn);
	end = ft_strjoin(start, "'");
	ft_err(end, err);
	free(start);
	free(end);
	return (SUCCESS);
}

/** @} */
