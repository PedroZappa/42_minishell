/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   640_exec_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:12:07 by passunca          #+#    #+#             */
/*   Updated: 2024/08/17 12:10:43 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup exec_children Execute Children
* @{
*
* @brief		Execute children
* @version		1.0
***/

#include "../inc/minishell.h"

void	ft_exec_child_first(t_shell *sh, int *outpipe)
{
	if (sh->cmds[0].in.name)
		ft_redir_in(sh, 0);
	if (sh->cmds[0].out.name)
		ft_redir_out(sh, 0);
	if (outpipe)
	{
		if (ft_pipe_setter(outpipe, STDOUT_FILENO) == PIPE_FAIL)
		{
			ft_close_pipes(NULL, outpipe);
			ft_fork_exit(sh, PIPE_ERR, FAILURE);
		}
	}
	if (sh->cmds[0].argv[0])
		ft_exec_cmd(sh, ft_exec_check(sh->cmds[0].argv[0]), NO_PIPE);
	ft_free_sh(sh);
	exit(SUCCESS);
}

void	ft_exec_child_i(t_shell *sh, int **pipes, int i)
{
	if (sh->cmds[i].in.name)
		ft_redir_in(sh, i);
	else if (ft_pipe_setter(pipes[0], STDIN_FILENO) == PIPE_FAIL)
	{
		ft_close_pipes(pipes[0], pipes[1]);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
	if (sh->cmds[i].out.name)
		ft_redir_out(sh, i);
	else if (ft_pipe_setter(pipes[1], STDOUT_FILENO) == PIPE_FAIL)
	{
		ft_close_pipes(pipes[0], pipes[1]);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
	ft_close_pipes(pipes[0], pipes[1]);
	if (sh->cmds[i].argv[0])
		ft_exec_cmd(sh, ft_exec_check(sh->cmds[i].argv[0]), i);
	free(pipes);
	ft_free_sh(sh);
	exit(SUCCESS);
}

void	ft_exec_child_last(t_shell *sh, int *inpipe, int i)
{
	if (sh->cmds[i].in.name)
		ft_redir_in(sh, i);
	else if (ft_pipe_setter(inpipe, STDIN_FILENO) == PIPE_FAIL)
	{
		ft_close_pipes(inpipe, NULL);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
	if (sh->cmds[i].out.name)
		ft_redir_out(sh, i);
	ft_close_pipes(inpipe, NULL);
	if (sh->cmds[i].argv[0])
		ft_exec_cmd(sh, ft_exec_check(sh->cmds[i].argv[0]), i);
	ft_free_sh(sh);
	exit(SUCCESS);
}

/** @} */
