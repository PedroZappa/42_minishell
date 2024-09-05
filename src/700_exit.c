/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   700_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 21:22:16 by passunca          #+#    #+#             */
/*   Updated: 2024/07/16 14:56:54 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup exit Exit built-in
* @{
*
* @brief		Exit built-in
* @version		1.0
***/

#include "../inc/minishell.h"

void	ft_kill(t_shell *sh, int exit_code);

/// @brief			exit built-in
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
int	ft_exit(t_shell *sh, int n)
{
	if (sh->cmds[n].argc > 2)
		ft_err("bash: exit: too many arguments\n", FAILURE);
	if (sh->cmds[n].argc == 1)
		ft_kill(sh, 0);
	if (sh->cmds[n].argc == 2)
	{
		if (ft_isnum(sh->cmds[n].argv[1]))
			ft_kill(sh, ft_atoi(sh->cmds[n].argv[1]));
	}
	return (SUCCESS);
}

void	ft_kill(t_shell *sh, int exit_code)
{
	ft_fprintf(STDOUT_FILENO, "exit\n");
	errno = exit_code;
	ft_free_sh(sh);
	exit(exit_code);
}

/** @} */
