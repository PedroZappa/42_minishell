/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   640_exec_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:12:07 by passunca          #+#    #+#             */
/*   Updated: 2024/08/17 10:17:46 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup exec_children Execute Children
* @{
*
* @brief		Execute children
* @version		1.0
***/

#include "../inc/minishell.h"

void	ft_exec_child_first(t_shell *sh, int *pipeout);
int		ft_exec_child_i(t_shell *sh, int **pipes, int i);
int		ft_exec_child_last(t_shell *sh, int *pipein, int i);

/// @brief			Execute one command as a child process
/// @param sh		Pointer to a t_shell struct
/// @param outpipe	Pointer to an int
void	ft_exec_child(t_shell *sh, int *outpipe)
{
	(void)outpipe;
	// TODO: Handle redirections & pipes
	if (sh->cmds[0].argv[0])
		ft_exec_cmd(sh, ft_exec_check(sh->cmds[0].argv[0]), NO_PIPE);
	ft_free_sh(sh);
	exit(SUCCESS);
}

void	ft_exec_child_first(t_shell *sh, int *pipeout)
{
	(void)sh;
	(void)pipeout;
}

int	ft_exec_child_i(t_shell *sh, int **pipes, int i)
{
	(void)sh;
	(void)pipes;
	(void)i;
	return (SUCCESS);
}

int	ft_exec_child_last(t_shell *sh, int *pipein, int i)
{
	(void)sh;
	(void)pipein;
	(void)i;
	return (SUCCESS);
}

/** @} */
