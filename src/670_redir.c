/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   680_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:40:09 by passunca          #+#    #+#             */
/*   Updated: 2024/08/17 12:02:49 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @defgroup redirects Redirects
* @{
*
* @brief		Redirects
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			Redirect input
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Pointer to a t_cmd struct
void	ft_redir_in(t_shell *sh, t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->in_fd = open(cmd->in[i].name, O_CREAT | O_RDONLY,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (cmd->in_fd < 0)
		ft_fork_exit(sh, cmd->in[i].name, FAILURE);
	if (ft_pipe_setter_fd(sh, cmd->in_fd, STDIN_FILENO) == PIPE_FAIL)
	{
		close(cmd->in_fd);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
}

/// @brief			Redirect output
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Pointer to a t_cmd struct
void	ft_redir_out(t_shell *sh, t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->out_fd = open(cmd->out[0].name, O_CREAT | O_WRONLY,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (cmd->out_fd < 0)
		ft_fork_exit(sh, cmd->out[i].name, FAILURE);
	if ((cmd->out_fd != 1)
		&& (ft_pipe_setter_fd(sh, cmd->out_fd, STDOUT_FILENO) == PIPE_FAIL))
	{
		close(cmd->out_fd);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
}

/** @} */
