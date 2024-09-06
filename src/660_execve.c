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

void	ft_execve_path(char **path, char **argv, char **envp);
int		ft_stat_path(char *cmd);

/// @brief			Execute command with execve w/ absolute or relative path
/// @param path		Pointer to PATH array
/// @param argv		Pointer to command arguments array
/// @param envp		Pointer to environment variables array
void	ft_execve(char **path, char **argv, char **envp)
{
	int	execve_err;

	if (ft_strchr(argv[0], '/') != NULL)
	{
		execve_err = execve(*argv, argv, envp);
		if (execve_err != EXECVE_ERR)
			return ;
		ft_stat_path(argv[0]);
		return ;
	}
	if (path == NULL)
		return ;
	ft_execve_path(path, argv, envp);
}

/// @brief			Get stat of a path
/// @param cmd		Pointer to command
int	ft_stat_path(char *cmd)
{
	t_stat	sb;
	int		stat_ret;

	memset(&sb, 0, sizeof(t_stat));
	stat_ret = stat(cmd, &sb);
	if (stat_ret == -1)
	{
		ft_fprintf(STDERR_FILENO, "bash: %s: No such file or directory\n", cmd);
		g_exit = 127;
		return (1);
	}
	if ((sb.st_mode & __S_IFMT) == __S_IFDIR)
	{
		ft_fprintf(STDERR_FILENO, "bash: %s: Is a directory\n", cmd);
		g_exit = 126;
		return (1);
	}
	return (0);
}

/// @brief			Execute command with relative path
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
		if (access(exec_path, X_OK) == 0)
			execve_err = execve(exec_path, argv, envp);
		++i;
		free(exec_path);
	}
	if (execve_err == EXECVE_ERR)
	{
		g_exit = 127;
		ft_cmd_err(argv[0], g_exit);
	}
}

/** @} */
