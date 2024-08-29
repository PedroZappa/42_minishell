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

void	ft_redir_in(t_shell *sh, int i)
{
	int	fd;

	if (sh->cmds[i].in.flag >= 0)
	{
		fd = open(sh->cmds[i].in.name, sh->cmds[i].in.flag,
				S_IRWXU | S_IRGRP | S_IROTH);
		if (fd < 0)
			ft_fork_exit(sh, sh->cmds[i].in.name, FAILURE);
		if (ft_pipe_setter_fd(sh, fd, STDIN_FILENO) == PIPE_FAIL)
		{
			close(fd);
			ft_fork_exit(sh, PIPE_ERR, FAILURE);
		}
	}
}

void	ft_redir_out(t_shell *sh, int i)
{
	int	fd;

	fd = open(sh->cmds[i].out.name, sh->cmds[i].out.flag,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (fd < 0)
		ft_fork_exit(sh, sh->cmds[i].out.name, FAILURE);
	if ((fd != 1) && (ft_pipe_setter_fd(sh, fd, STDOUT_FILENO) == PIPE_FAIL))
	{
		close(fd);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
}
