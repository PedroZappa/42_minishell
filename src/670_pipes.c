/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   670_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:19:37 by passunca          #+#    #+#             */
/*   Updated: 2024/08/16 11:26:02 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief			Set pipes
/// @param pipe		Pointer to a pipe
/// @param end		End of pipe (read or write)
/// @return			SUCCESS(0)
int	ft_pipe_setter(int *pipe, int end)
{
	if (pipe[end] != end)
		return (dup2(pipe[end], end));
	return (SUCCESS);
}

/// @brief			Close pipes
/// @param pipe0	Pointer to a pipe0
/// @param pipe1	Pointer to a pipe1
void	ft_close_pipes(int *pipe0, int *pipe1)
{
	if (pipe0)
	{
		close(pipe0[0]);
		close(pipe0[1]);
	}
	if (pipe1)
	{
		close(pipe1[0]);
		close(pipe1[1]);
	}
}
