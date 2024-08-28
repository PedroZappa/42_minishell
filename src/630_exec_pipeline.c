/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   630_exec_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 08:39:57 by passunca          #+#    #+#             */
/*   Updated: 2024/08/17 10:19:27 by passunca         ###   ########.fr       */
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

int		ft_exec_first(t_shell *sh, int *outpipe);
int		ft_exec_loop(t_shell *sh, int *pipe0, int *pipe1);
int		ft_exec_cmd_i(t_shell *sh, int **pipes, int i);
int		ft_exec_last(t_shell *sh, int *inpipe);

/// @brief			Execute a pipeline of commands
/// @param sh		Pointer to a t_shell struct
/// @return			SUCCESS(0)
///					FAILURE(1)
int	ft_exec_pipeline(t_shell *sh)
{
	int	pipe0[2];
	int	pipe1[2];
	int	cmd_idx;

	ft_fork_sigset();
	if (ft_exec_first(sh, pipe0) == FAILURE)
		return (FAILURE);
	cmd_idx = ft_exec_loop(sh, pipe0, pipe1);
	if (cmd_idx == CMD_FAIL)
		return (FAILURE);
	if ((cmd_idx % 2 == 0) && (ft_exec_last(sh, pipe1) == FAILURE))
		return (FAILURE);
	if ((cmd_idx % 2 == 1) && (ft_exec_last(sh, pipe0) == FAILURE))
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

/// @brief			Execute first command in pipeline
/// @param sh		Pointer to a t_shell struct
/// @param outpipe	Pointer to an int (output pipe)
/// @return			SUCCESS(0)
int	ft_exec_first(t_shell *sh, int *outpipe)
{
	pid_t	pid;

	if (pipe(outpipe) == PIPE_FAIL)
		return (ft_return_err("", errno, FAILURE));
	pid = fork();
	if (pid == PID_FAIL)
		return (ft_return_err("", errno, FAILURE));
	if (pid == SUCCESS)
		ft_exec_child_first(sh, outpipe);
	close(outpipe[1]);
	return (SUCCESS);
}

/// @brief			Execute in-between commands in pipeline
/// @param sh		Pointer to a t_shell struct
/// @param pipe0	Pointer to an int (input pipe)
/// @param pipe1	Pointer to an int (output pipe)
/// @return			SUCCESS(cmd_i)
///					FAILURE(-1)
int	ft_exec_loop(t_shell *sh, int *pipe0, int *pipe1)
{
	int	**pipes;
	int	cmd_i;
	int	i;

	i = 0;
	cmd_i = 0;
	while (++i < (sh->n_cmds - 1))
	{
		if ((cmd_i % 2) == 0)
		{
			pipes = ft_pipe_init(sh->path, pipe0, pipe1);
			if (ft_exec_cmd_i(sh, pipes, i) == FAILURE)
				return (CMD_FAIL);
		}
		else
		{
			pipes = ft_pipe_init(sh->path, pipe0, pipe1);
			if (ft_exec_cmd_i(sh, pipes, i) == FAILURE)
				return (CMD_FAIL);
		}
		++cmd_i;
	}
	return (cmd_i);
}

/// @brief			Execute i-th command in pipeline
/// @param sh		Pointer to a t_shell struct
/// @param inpipe	Pointer to an int (input & output pipe)
/// @return			SUCCESS(0)
///					FAILURE(1)
int	ft_exec_cmd_i(t_shell *sh, int **pipes, int i)
{
	pid_t	pid;

	if (!pipes)
		return (ft_return_err("", errno, FAILURE));
	pid = fork();
	if (pid == PID_FAIL)
		return (ft_return_err("", errno, FAILURE));
	if (pid == SUCCESS)
		ft_exec_child_i(sh, pipes, i);
	ft_close_pipes(pipes[0], pipes[1]);
	free(pipes);
	return (SUCCESS);
}

/// @brief			Execute last command in pipeline
/// @param sh		Pointer to a t_shell struct
/// @param inpipe	Pointer to an int (input pipe)
/// @return			SUCCESS(0)
///					FAILURE(1)
int	ft_exec_last(t_shell *sh, int *inpipe)
{
	pid_t	pid;
	int		i;

	i = (sh->n_cmds - 1);
	pid = fork();
	if (pid == PID_FAIL)
		return (ft_return_err("", errno, FAILURE));
	if (pid == SUCCESS)
		ft_exec_child_last(sh, inpipe, i);
	ft_close_pipes(inpipe, NULL);
	return (SUCCESS);
}

/** @} */
