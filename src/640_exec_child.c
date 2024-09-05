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

/// @brief			Execute first command in pipeline
/// @param sh		Pointer to a t_shell struct
void	ft_exec_child_first(t_shell *sh)
{
	if (sh->n_pipes != 0)
		ft_pipe_setter(sh, 0, STDOUT_FILENO);
	ft_close_pipes(sh);
	if (sh->cmds[0].argv[0])
		ft_exec_cmd(sh, ft_exec_check(sh->cmds[0].argv[0]), NO_PIPE);
	ft_free_sh(sh);
	exit(g_exit);
}

/// @brief			Execute command in pipeline
/// @param sh		Pointer to a t_shell struct
/// @param i		Command index
void	ft_exec_child_i(t_shell *sh, int i)
{
	ft_pipe_setter(sh, i - 1, STDIN_FILENO);
	ft_pipe_setter(sh, i, STDOUT_FILENO);
	ft_close_pipes(sh);
	if (sh->cmds[i].argv[0])
		ft_exec_cmd(sh, ft_exec_check(sh->cmds[i].argv[0]), i);
	ft_free_sh(sh);
	exit(g_exit);
}

/// @brief			Execute last command in pipeline
/// @param sh		Pointer to a t_shell struct
/// @param i		Command index
void	ft_exec_child_last(t_shell *sh, int i)
{
	ft_pipe_setter(sh, i - 1, STDIN_FILENO);
	ft_close_pipes(sh);
	if (sh->cmds[i].argv[0])
		ft_exec_cmd(sh, ft_exec_check(sh->cmds[i].argv[0]), i);
	ft_free_sh(sh);
	exit(g_exit);
}

/** @} */
