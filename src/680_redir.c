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

#include "../inc/minishell.h"

void	ft_redir_in(t_shell *sh, t_cmd *cmd)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(cmd->in[i].name, O_CREAT | O_RDONLY,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (fd < 0)
		ft_fork_exit(sh, cmd->in[i].name, FAILURE);
	if (ft_pipe_setter_fd(sh, fd, STDIN_FILENO) == PIPE_FAIL)
	{
		close(fd);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
}

void	ft_redir_out(t_shell *sh, t_cmd *cmd)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(cmd->out[0].name, O_CREAT | O_WRONLY,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (fd < 0)
		ft_fork_exit(sh, cmd->out[i].name, FAILURE);
	if ((fd != 1) && (ft_pipe_setter_fd(sh, fd, STDOUT_FILENO) == PIPE_FAIL))
	{
		close(fd);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
}
