/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   670_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:40:09 by passunca          #+#    #+#             */
/*   Updated: 2024/09/24 14:29:33 by gfragoso         ###   ########.fr       */
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

int	ft_redir_in_type(t_redir *redir);

/// @brief			Redirect input
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Pointer to a t_cmd struct
void	ft_redir_in(t_shell *sh, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->n_in)
	{
		if (cmd->in_fd != -1 && i > 0)
		{
			close(cmd->in_fd);
			if (cmd->in[i - 1].type == RD_IN_HD)
				unlink(cmd->in[i - 1].name);
			cmd->in_fd = -1;
		}
		cmd->in_fd = ft_redir_in_type(cmd->in + i);
		i++;
	}
	if (cmd->in_fd < 0)
		ft_fork_exit(sh, NULL, FAILURE);
	if (ft_pipe_setter_fd(sh, cmd->in_fd, STDIN_FILENO) == PIPE_FAIL)
	{
		close(cmd->in_fd);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
}

int	ft_redir_in_type(t_redir *redir)
{
	int	ret;

	ret = open(redir->name, O_RDONLY,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (ret == -1)
		g_exit = ft_no_file_err(redir->name);
	return (ret);
}

/// @brief			Redirect output
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Pointer to a t_cmd struct
void	ft_redir_out(t_shell *sh, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->n_out)
	{
		if (cmd->out_fd != -1)
		{
			close(cmd->out_fd);
			cmd->out_fd = -1;
		}
		cmd->out_fd = open(cmd->out[i].name, O_CREAT | O_WRONLY
				| (O_APPEND * (cmd->out[i].type == RD_OUT_APP)
					| (O_TRUNC * (cmd->out[i].type == RD_OUT))),
				S_IRWXU | S_IRGRP | S_IROTH);
		++i;
	}
	if (cmd->out_fd < 0)
		ft_fork_exit(sh, cmd->out[i - 1].name, FAILURE);
	if ((cmd->out_fd != 1)
		&& (ft_pipe_setter_fd(sh, cmd->out_fd, STDOUT_FILENO) == PIPE_FAIL))
	{
		close(cmd->out_fd);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
}

char	*ft_redir_heredoc_name(int i)
{
	char	*ret;
	char	*temp;

	temp = ft_itoa(i);
	ret = ft_strjoin(".heredoc_", temp);
	ft_free(temp);
	return (ret);
}

void	ft_redir_close(int *fd_in, int *fd_out)
{
	if (fd_in && *fd_in != -1)
	{
		close(*fd_in);
		*fd_in = -1;
	}
	if (fd_out && *fd_out != -1)
	{
		close(*fd_out);
		*fd_out = -1;
	}
}

/** @} */
