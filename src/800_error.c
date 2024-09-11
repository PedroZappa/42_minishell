/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   800_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:35:23 by passunca          #+#    #+#             */
/*   Updated: 2024/08/17 09:31:18 by passunca         ###   ########.fr       */
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
/// @note			Used all over the code base
int	ft_err(char *msg, int status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	g_exit = status;
	return (FAILURE);
}

/// @brief Create error message
/// @param tkn		Message to be printed
/// @return			SUCCESS(0)
int	ft_syntax_char_err(char tkn)
{
	ft_fprintf(STDERR_FILENO,
		"bash : syntax error near unexpected token `%c'\n", tkn);
	g_exit = 2;
	return (2);
}

/// @brief Create error message
/// @param tkn		Message to be printed
/// @return			SUCCESS(0)
int	ft_syntax_err(char *tkn)
{
	ft_fprintf(STDERR_FILENO,
		"bash : syntax error near unexpected token `%s'\n", tkn);
	g_exit = 2;
	return (2);
}

/// @brief			Print invalid flag error
/// @param cmd		Command name
/// @param cmd_flag	Flag name
/// @return			SUCCESS(ret)
int	ft_flag_err(char *cmd, char *cmd_flag)
{
	ft_fprintf(STDERR_FILENO, "%s: ’%s’: options & flags not supported\n",
		cmd, cmd_flag);
	return (2);
}

/// @brief			Print invalid command error
/// @param cmd		Command name
/// @param err		Error number
/// @return			SUCCESS(err)
int	ft_cmd_err(char *cmd, int err)
{
	ft_fprintf(STDERR_FILENO, "%s: command not found\n", cmd);
	return (err);
}

/** @} */
