/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   670_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:19:37 by passunca          #+#    #+#             */
/*   Updated: 2024/08/16 11:40:45 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// TODO: Handle pipe error 
int	**ft_pipe_init(char **path, int *pipe1, int *pipe2)
{
	int	**pipes;

	pipes = malloc(sizeof(int *) * 2);
	if (!pipes)
		return (ft_err(MALLOC_ERR, errno), NULL);
	if (pipe(pipe2) == -1)
		return (ft_pipe_err(path), NULL);
	pipes[0] = pipe1;
	pipes[1] = pipe2;
	return (pipes);
}

/// @brief			Set pipes
/// @param pipe		Pointer to a pipe
/// @param end		End of pipe (stdin or stdout)
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
