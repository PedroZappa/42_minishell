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

void	ft_exec_child_inner(t_shell *sh, t_cmd *cmd);
void	ft_exec_redir_set(t_shell *sh, t_cmd *cmd);

/// @brief			Execute first command in pipeline
/// @param sh		Pointer to a t_shell struct
void	ft_exec_child_first(t_shell *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmds;
	ft_exec_redir_set(sh, cmd);
	if (sh->n_pipes != 0)
		ft_pipe_setter(sh, 0, STDOUT_FILENO);
	ft_exec_child_inner(sh, cmd);
}

/// @brief			Execute command in pipeline
/// @param sh		Pointer to a t_shell struct
/// @param i		Command index
void	ft_exec_child_i(t_shell *sh, int i)
{
	t_cmd	*cmd;

	cmd = sh->cmds + i;
	ft_exec_redir_set(sh, cmd);
	ft_pipe_setter(sh, i - 1, STDIN_FILENO);
	ft_pipe_setter(sh, i, STDOUT_FILENO);
	ft_exec_child_inner(sh, cmd);
}

/// @brief			Execute last command in pipeline
/// @param sh		Pointer to a t_shell struct
/// @param i		Command index
void	ft_exec_child_last(t_shell *sh, int i)
{
	t_cmd	*cmd;

	cmd = sh->cmds + i;
	ft_exec_redir_set(sh, cmd);
	ft_pipe_setter(sh, i - 1, STDIN_FILENO);
	ft_exec_child_inner(sh, cmd);
}

void	ft_exec_child_inner(t_shell *sh, t_cmd *cmd)
{
	ft_pipe_close(sh, &cmd->in_fd, &cmd->out_fd);
	if (cmd->argv[0])
		ft_exec_cmd(sh, ft_exec_check(cmd->argv[0]), NO_PIPE);
	ft_free_sh(sh);
	exit(g_exit);
}

void	ft_exec_redir_set(t_shell *sh, t_cmd *cmd)
{
	if (cmd->n_in > 0)
		ft_redir_in(sh, cmd);
	if (cmd->n_out > 0)
		ft_redir_out(sh, cmd);
}

/** @} */
