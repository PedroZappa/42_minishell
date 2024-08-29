/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   670_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:19:37 by passunca          #+#    #+#             */
/*   Updated: 2024/08/16 11:53:57 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief			Initialize pipes
/// @param path		Pointer to a path
/// @param pipe1	Pointer to a pipe1
/// @param pipe2	Pointer to a pipe2
/// @return			Pointer to an array of pipes
/// @note			Used all over the code base
void	ft_pipe_init(t_shell *sh)
{
	if (pipe(sh->pipe) == PIPE_FAIL)
		return ;
}

/// @brief			Set pipes
/// @param pipe		Pointer to a pipe
/// @param in		Flag whether stdin or stdout
/// @return			SUCCESS(0)
int	ft_pipe_setter(t_shell *sh, int pipe, int in)
{
	if (dup2(sh->pipe[in], in) == PIPE_FAIL)
	{
		ft_close_pipes(sh, -1);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
	close(sh->pipe[1 - in]);
	if (dup2(pipe, 1 - in) == PIPE_FAIL)
	{
		ft_close_pipes(sh, -1);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
	return (SUCCESS);
}

/// @brief			Close pipes
/// @param pipe0	Pointer to a pipe0
/// @param pipe1	Pointer to a pipe1
void	ft_close_pipes(t_shell *sh, int fd)
{
	if (sh->pipe[0] > 0)
	{
		close(sh->pipe[0]);
		sh->pipe[0] = -1;
	}
	if (sh->pipe[1] > 0)
	{
		close(sh->pipe[1]);
		sh->pipe[1] = -1;
	}
	if (fd > 0)
		close(fd);
}
