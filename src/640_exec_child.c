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

void	ft_exec_child_first(t_shell *sh, int *outpipe);
int		ft_exec_child_i(t_shell *sh, int **pipes, int i);
int		ft_exec_child_last(t_shell *sh, int *inpipe, int i);

void	ft_exec_child_first(t_shell *sh, int *outpipe)
{
	// TODO: Handle redirections
	if (outpipe)
	{
		if (ft_pipe_setter(outpipe, STDOUT_FILENO) == PIPE_FAIL)
		{
			ft_close_pipes(NULL, outpipe);
			ft_fork_exit(sh, PIPE_ERR, FAILURE);
		}
	}
	if (sh->cmds[0].argv[0])
		ft_exec_cmd(sh, ft_exec_check(sh->cmds[0].argv[0]), NO_PIPE);
	ft_free_sh(sh);
	exit(SUCCESS);
}

int	ft_exec_child_i(t_shell *sh, int **pipes, int i)
{
	(void)sh;
	(void)pipes;
	(void)i;
	return (SUCCESS);
}

int	ft_exec_child_last(t_shell *sh, int *inpipe, int i)
{
	(void)sh;
	(void)inpipe;
	(void)i;
	return (SUCCESS);
}

/** @} */
