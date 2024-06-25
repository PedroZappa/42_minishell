/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   700_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 21:22:16 by passunca          #+#    #+#             */
/*   Updated: 2024/06/22 10:25:58 by passunca         ###   ########.fr       */
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

static void	ft_kill(t_shell *sh, int sig);

/// @brief			exit built-in
/// @param sh		Pointer to a t_shell struct
/// ...
int	ft_exit(t_shell *sh, int n)
{
	if (sh->cmds[n].argc == 1)
		ft_kill(sh, 0);
	else if (sh->cmds[n].argc > 1)
		g_exit = ft_err("exit: too many arguments", FAILURE);
	return (SUCCESS);
}

static void	ft_kill(t_shell *sh, int sig)
{
	ft_putstr_fd("exit\n ", STDOUT_FILENO);
	errno = sig;
	ft_free_sh(sh);
	exit(g_exit);
}	

/** @} */
