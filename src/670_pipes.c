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
int	**ft_pipe_init(char **path, int *pipe0, int *pipe1)
{
	int	**pipes;

	pipes = (int **)malloc(sizeof(int *) * 2);
	if (!pipes)
		return (ft_err(MALLOC_ERR, errno), NULL);
	if (pipe(pipe1) == PIPE_FAIL)
		return (ft_pipe_err(path), NULL);
	pipes[0] = pipe0;
	pipes[1] = pipe1;
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
