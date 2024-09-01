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
		ft_close_pipes(sh);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
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
		ft_close_pipes(sh);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
	return (SUCCESS);
}

/// @brief			Close pipes
/// @param sh		Pointer to a t_shell struct
void	ft_close_pipes(t_shell *sh)
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
		free(sh->pipes[i]);
		sh->pipes[i] = NULL;
	}
	free(sh->pipes);
	sh->pipes = NULL;
}
