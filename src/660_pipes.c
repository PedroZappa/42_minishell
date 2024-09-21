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

/**
* @defgroup pipes Pipes
* @{
*
* @brief		Pipe logic
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			Initialize pipes
/// @param sh		Pointer to a t_shell struct
/// @note			Used all over the code base
void	ft_pipe_init(t_shell *sh)
{
	int	i;

	i = 0;
	sh->pipes = ft_calloc(sh->n_pipes, sizeof(int *));
	while (i < sh->n_pipes)
	{
		sh->pipes[i] = ft_calloc(2, sizeof(int));
		if (pipe(sh->pipes[i]) == PIPE_FAIL)
			return ((void)ft_return_err("Couldn't create pipes",
					errno, FAILURE));
		i++;
	}
}

/// @brief			Set pipes
/// @param sh		Pointer to a t_shell struct
/// @param i		Pipe number
/// @param out	Flag whether stdin or stdout
/// @return			SUCCESS(0)
int	ft_pipe_setter(t_shell *sh, int i, int out)
{
	if (out < 0 || out > 1)
		return (FAILURE);
	if (dup2(sh->pipes[i][out], out) == PIPE_FAIL)
	{
		ft_pipe_close(sh, NULL, NULL);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
	close(out);
	return (SUCCESS);
}

/// @brief			Set pipes
/// @param sh		Pointer to a t_shell struct
/// @param fd		Pointer to a fd
/// @param out		Flag whether stdin or stdout
/// @return			SUCCESS(0)
int	ft_pipe_setter_fd(t_shell *sh, int fd, int out)
{
	if ((out > 1 || out < 0) && fd < 0)
		return (FAILURE);
	if (dup2(fd, out) == PIPE_FAIL)
	{
		ft_pipe_close(sh, &fd, NULL);
		close(fd);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

/// @brief			Close pipes
/// @param sh		Pointer to a t_shell struct
void	ft_pipe_close(t_shell *sh, int *fd_in, int *fd_out)
{
	int	i;

	if (sh->pipes == NULL)
		return ;
	i = -1;
	while (++i < sh->n_pipes)
	{
		if (sh->pipes[i] == NULL)
			continue ;
		close(sh->pipes[i][0]);
		close(sh->pipes[i][1]);
		ft_vfree(sh->pipes[i]);
		sh->pipes[i] = NULL;
	}
	ft_redir_close(fd_in, fd_out);
	ft_vfree(sh->pipes);
	sh->pipes = NULL;
}

void	ft_pipe_reset(void)
{
	dup2(0, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
}

/** @} */
