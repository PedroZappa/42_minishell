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

static void	ft_kill(t_shell *sh, int sig);

// TODO: Fix break if exit is not exactly exit

/// @brief			exit built-in
/// @param sh		Pointer to a t_shell struct
/// ...
int	ft_exit(t_shell *sh, int n)
{
	if (sh->cmds[n].argc == 1)
		ft_kill(sh, EXIT_SUCCESS);
	else if (sh->cmds[n].argc == 2)
		ft_kill(sh, ft_abs(ft_atoi(sh->cmds[n].argv[1])));
	else if (sh->cmds[n].argc > 2)
		ft_fprintf(STDERR_FILENO, "exit\nbash: %s: too many arguments\n",
			sh->cmds[n].argv[0], sh->cmds[n].argv[1]);
	return (SUCCESS);
}

/// @brief			exit built-in
/// @param sh		Pointer to a t_shell struct
/// @param sig		Signal number
static void	ft_kill(t_shell *sh, int sig)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	errno = sig;
	ft_free_sh(sh);
	exit(errno);
}

/** @} */
