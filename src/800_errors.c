/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   800_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:35:23 by passunca          #+#    #+#             */
/*   Updated: 2024/08/16 11:37:10 by passunca         ###   ########.fr       */
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
/// - Print error message
/// @param tkn		Message to be printed
/// @param err		Error number
/// @return			SUCCESS(0)
int	ft_syntax_err(char *tkn, int err)
{
	ft_fprintf(STDERR_FILENO,
		"bash : syntax error near unexpected token '%s'\n", tkn);
	return (err);
}

/// @brief			Print invalid flag error
/// @details
/// - Print error message
/// @param cmd		Command name
/// @param cmd_flag	Flag name
/// @param err		Error number
/// @return			SUCCESS(ret)
int	ft_flag_err(char *cmd, char *cmd_flag, int err)
{
	ft_fprintf(STDERR_FILENO, "%s: ’%s’: options & flags not supported\n",
		cmd, cmd_flag);
	return (err);
}

/// @brief			Print invalid command error
/// @details
/// - Print error message
/// @param cmd		Command name
/// @param err		Error number
/// @return			SUCCESS(err)
int	ft_cmd_err(char *cmd, int err)
{
	ft_fprintf(STDERR_FILENO, "%s: command not found\n", cmd);
	return (err);
}

/// @brief			Print invalid command error with argument
/// @param cmd		Command name
/// @param arg		Invalid Argument
/// @param err		Error number
/// @return			SUCCESS(err)
int	ft_bash_err(char *cmd, char *arg, int err)
{
	ft_fprintf(STDERR_FILENO,
		"bash: %s: %s: No such file or directory\n", cmd, arg);
	return (err);
}

/// @brief			Print pipe error
/// @param path		Path to be freed
/// @return			FAILURE(1)
int	ft_pipe_err(char **path)
{
	ft_fprintf(STDERR_FILENO, "Error: pipe failure\n");
	g_exit = 1;
	return (ft_free_arr(path), FAILURE);
}

/** @} */
