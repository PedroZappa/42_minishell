/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   630_exec_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 08:39:57 by passunca          #+#    #+#             */
/*   Updated: 2024/07/08 20:19:05 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup execute Execute Pipeline
* @{
*
* @brief		Execute a pipeline of commands
* @version		1.0
***/

#include "../inc/minishell.h"

int	ft_exec_first(t_shell *sh, char **path, int *pipeout);
int	ft_exec_mid(t_shell *sh, int *pipe0, int *pipe1);
int	ft_exec_last(t_shell *sh, int *pipein);

/// @brief			Execute a pipeline of commands
/// @param sh		Pointer to a t_shell struct
/// @return			SUCCESS(0)
int	ft_exec_pipeline(t_shell *sh)
{
	int	pipe0[2];
	int	pipe1[2];
	int	cmd_idx;

	ft_fork_sigset();
	if (ft_exec_first(sh, sh->path, pipe0) == FAILURE)
		return (FAILURE);
	cmd_idx = ft_exec_mid(sh, pipe0, pipe1);
	if (cmd_idx == CMD_FAIL)
		return (FAILURE);
	if ((cmd_idx % 2 == 0) && (ft_exec_last(sh, pipe0) == FAILURE))
		return (FAILURE);
	if ((cmd_idx % 2 == 1) && (ft_exec_last(sh, pipe1) == FAILURE))
		return (FAILURE);
	if (ft_exec_last(sh, pipe1) == FAILURE)
		return (FAILURE);
	wait(&g_exit);
	while (cmd_idx--)
		wait(&g_exit);
	wait(&g_exit);
	if (WIFSIGNALED(g_exit))
		g_exit = (128 + WTERMSIG(g_exit));
	else if (WIFEXITED(g_exit))
		g_exit = WEXITSTATUS(g_exit);
	return (SUCCESS);
}

int	ft_exec_first(t_shell *sh, char **path, int *pipeout)
{
	(void)sh;
	(void)path;
	(void)pipeout;
	return (SUCCESS);
}

int	ft_exec_mid(t_shell *sh, int *pipe0, int *pipe1)
{
	(void)sh;
	(void)pipe0;
	(void)pipe1;
	return (SUCCESS);
}

int	ft_exec_last(t_shell *sh, int *pipein)
{
	(void)sh;
	(void)pipein;
	return (SUCCESS);
}

/** @} */
