/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   810_error2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 09:30:27 by passunca          #+#    #+#             */
/*   Updated: 2024/08/17 09:40:00 by passunca         ###   ########.fr       */
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

/// @brief				Print error message
/// @param msg			Message to be printed
/// @param err_code		Error Code
/// @param exit_status	Exit status
/// @return			SUCCESS(0)
int	ft_return_err(char *msg, int err_code, int exit_status)
{
	if (!exit_status || !msg)
		ft_fprintf(STDERR_FILENO, "bash: ");
	g_exit = err_code;
	if (exit_status)
	{
		if (!err_code)
			g_exit = errno;
		ft_fprintf(STDERR_FILENO, "%s\n", msg);
	}
	else
		ft_fprintf(STDERR_FILENO, "%s\n", msg);
	return (exit_status);
}

/// @brief				Print error message, free shell & exit
/// @param sh			Pointer to a t_shell struct
/// @param msg			Message to be printed
/// @param err_code		Error Code
void	ft_fork_exit(t_shell *sh, char *msg, int err_code)
{
	ft_return_err(msg, err_code, FAILURE);
	ft_free_sh(sh);
	exit(err_code);
}

/** @} */