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
* @defgroup execute Execute
* @{
*
* @brief		Execute commands
* @version		1.0
***/

#include "../inc/minishell.h"

void	ft_execve_abs(char **cmd, char **argv, char **envp);
void	ft_execve_path(char **path, char **argv, char **envp);

void	ft_execve(char **path, char **argv, char **envp)
{
	(void)path;
	(void)argv;
	(void)envp;
	if ((*argv[0] == '/') || (*argv[0] == '.'))
	{
		ft_execve_abs(path, argv, envp);
		return ;
	}
	if (path)
		ft_execve_path(path, argv, envp);
	else
		return ;
}

// TODO: Handle Absolute Paths
void	ft_execve_abs(char **cmd, char **argv, char **envp)
{
	(void)cmd;
	(void)argv;
	(void)envp;
}

// TODO: Handle Relative Paths
void	ft_execve_path(char **path, char **argv, char **envp)
{
	(void)path;
	(void)argv;
	(void)envp;
}

/** @} */
