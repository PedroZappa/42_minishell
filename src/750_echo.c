/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   750_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:24:56 by passunca          #+#    #+#             */
/*   Updated: 2024/07/20 17:21:40 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup main Main
* @{
*
* @brief		Minishell main function
* @version		1.0
***/

#include "../inc/minishell.h"

static int	ft_is_nflag(char *arg);

/// @brief			Echo built-in
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Pointer to t_cmd struct
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_echo(t_shell *sh, t_cmd *cmd)
{
	int	sentinel;
	int	i;

	sentinel = '\n';
	i = 0;
	while (cmd->argv[++i] && ft_is_nflag(cmd->argv[i]))
		sentinel = '\0';
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
		if (cmd->argv[i + 1])
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

/** @} */
