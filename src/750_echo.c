/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   750_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:24:56 by passunca          #+#    #+#             */
/*   Updated: 2024/07/10 17:31:54 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_is_nflag(char *arg);

/// @brief			Echo built-in
/// @details
/// - Skip dash
/// - Check for 'n's (however many)
///
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_echo(t_shell *sh, int n)
{
	int	sentinel;
	int	i;

	ft_update_last_cmd(sh);
	i = 0;
	sentinel = '\n';
	while (sh->cmds[n].argv[i++] && ft_is_nflag(sh->cmds[n].argv[i]))
		sentinel = '\0';
	while (sh->cmds[n].argv[i])
	{
		ft_putstr_fd(sh->cmds[n].argv[i], STDOUT_FILENO);
		if (sh->cmds[n].argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		++i;
	}
	ft_putchar_fd(sentinel, STDOUT_FILENO);
	return (SUCCESS);
}

/// @brief		Check for -n flag
/// @param arg	Argument to check
/// @return		SUCCESS(1)
/// @return		FAILURE(0)
static int	ft_is_nflag(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (!FAILURE);
	i = 0;
	while (arg[++i])
		if (arg[i] != 'n')
			return (!FAILURE);
	return (!SUCCESS);
}
