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

void	ft_exec_child_first(t_shell *sh)
{
	if (sh->n_pipes != 0)
		ft_pipe_setter(sh, 0, STDOUT_FILENO);
	if (sh->cmds[0].in.name)
		ft_redir_in(sh, 0);
	if (sh->cmds[0].out.name)
		ft_redir_out(sh, 0);
	ft_close_pipes(sh);
	if (sh->cmds[0].argv[0])
		ft_exec_cmd(sh, ft_exec_check(sh->cmds[0].argv[0]), NO_PIPE);
	ft_free_sh(sh);
	exit(SUCCESS);
}

void	ft_exec_child_i(t_shell *sh, int i)
{
	ft_pipe_setter(sh, i - 1, STDIN_FILENO);
	ft_pipe_setter(sh, i, STDOUT_FILENO);
	if (sh->cmds[i].in.name)
		ft_redir_in(sh, i);
	if (sh->cmds[i].out.name)
		ft_redir_out(sh, i);
	ft_close_pipes(sh);
	if (sh->cmds[i].argv[0])
		ft_exec_cmd(sh, ft_exec_check(sh->cmds[i].argv[0]), i);
	ft_free_sh(sh);
	exit(SUCCESS);
}

void	ft_exec_child_last(t_shell *sh, int i)
{
	ft_pipe_setter(sh, i - 1, STDIN_FILENO);
	if (sh->cmds[i].in.name)
		ft_redir_in(sh, i);
	if (sh->cmds[i].out.name)
		ft_redir_out(sh, i);
	ft_close_pipes(sh);
	if (sh->cmds[i].argv[0])
		ft_exec_cmd(sh, ft_exec_check(sh->cmds[i].argv[0]), i);
	ft_free_sh(sh);
	exit(SUCCESS);
}

/** @} */
