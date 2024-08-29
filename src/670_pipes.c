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

/// @brief			Set pipes
/// @param sh		Pointer to a t_shell struct
/// @param in		Flag whether stdin or stdout
/// @return			SUCCESS(0)
int	ft_pipe_setter(t_shell *sh, int in)
{
	if (sh->pipe[in] == -1 || in < 0)
		return (FAILURE);
	if (dup2(sh->pipe[1 - in], 1 - in) == PIPE_FAIL)
	{
		ft_close_pipes(sh);
		ft_fork_exit(sh, PIPE_ERR, FAILURE);
	}
	close(sh->pipe[in]);
	return (SUCCESS);
}

/// @brief			Set pipes
/// @param sh		Pointer to a t_shell struct
/// @param fd		Pointer to a fd
/// @param in		Flag whether stdin or stdout
/// @return			SUCCESS(0)
int ft_pipe_setter_fd(t_shell *sh, int fd, int in)
{
	if ((in > 1 || in < 0) && fd < 0)
		return (FAILURE);
	if (dup2(fd, 1 - in) == PIPE_FAIL)
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
}
