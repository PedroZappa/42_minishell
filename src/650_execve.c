/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   650_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 21:29:48 by passunca          #+#    #+#             */
/*   Updated: 2024/06/30 21:44:45 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup ft_execve Execute commands using execve
* @{
*
* @brief		Execute commands using execve
* @version		1.0
***/

#include "../inc/minishell.h"

void	ft_execve_abs(char **cmd, char **envp);
void	ft_execve_path(char **path, char **argv, char **envp);

/// @brief			Execute command with execve w/ absolute or relative path
/// @details
/// - If command name starts with '.' or '/'
/// 	- Execute command with absolute path
/// - Else if PATH is not NULL
/// 	- Execute command with relative path
/// - Else
/// @param path		Pointer to PATH array
/// @param argv		Pointer to command arguments array
/// @param envp		Pointer to environment variables array
void	ft_execve(char **path, char **argv, char **envp)
{
	if ((*argv[0] == '.') || (*argv[0] == '/'))
		ft_execve_abs(argv, envp);
	else if (path)
		ft_execve_path(path, argv, envp);
	else
		g_exit = errno;
}

/// @brief			Execute command with absolute path
/// @param cmd		Pointer to command
/// @param envp		Pointer to environment variables array
void	ft_execve_abs(char **argv, char **envp)
{
	if (execve(*argv, argv, envp) == EXECVE_ERR)
		g_exit = errno;
}

/// @brief			Execute command with relative path
/// @details
/// - Loop through PATH array searching for executable
///		- Concatenate PATH and command
///		- Attempt execve
///		- If execve fails increment PATH index and try again
///	- If after PATH search execve fails, set errno
///	- Free exec_path
/// @param path		Pointer to PATH array
/// @param argv		Pointer to command arguments array
/// @param envp		Pointer to environment variables array
void	ft_execve_path(char **path, char **argv, char **envp)
{
	char	*exec_path;
	int		execve_err;
	int		i;

	i = 0;
	execve_err = EXECVE_ERR;
	while ((execve_err == EXECVE_ERR) && path[i])
	{
		exec_path = ft_strjoin(path[i], *argv);
		if (!exec_path)
			break ;
		execve_err = execve(exec_path, argv, envp);
		++i;
		free(exec_path);
	}
	if (execve_err == EXECVE_ERR)
		g_exit = errno;
}

/** @} */
