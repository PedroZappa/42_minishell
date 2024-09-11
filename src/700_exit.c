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
#include <unistd.h>

void	ft_kill(t_shell *sh, int exit_code);
int		ft_isnum(char *str);

/// @brief			exit built-in
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Pointer to t_cmd struct
int	ft_exit(t_shell *sh, t_cmd *cmd)
{
	if (cmd->argc > 2)
	{
		ft_fprintf(STDOUT_FILENO, "exit\n");
		if (!ft_isnum(cmd->argv[1]))
		{
			ft_fprintf(STDERR_FILENO,
				"bash: exit: %s: numeric argument required\n", cmd->argv[1]);
			ft_kill(sh, 2);
		}
		else
			ft_err("bash: exit: too many arguments\n", FAILURE);
	}
	if (cmd->argc == 1)
		ft_kill(sh, 0);
	if (cmd->argc == 2)
	{
		if (ft_isnum(cmd->argv[1]))
			ft_kill(sh, ft_atoi(cmd->argv[1]));
		else
			ft_fprintf(STDERR_FILENO,
				"bash: exit: %s: numeric argument required\n", cmd->argv[1]);
	}
	return (SUCCESS);
}

/// @brief			Free shell and exit
/// @param sh		Pointer to a t_shell struct
/// @param exit_code	Exit code
void	ft_kill(t_shell *sh, int exit_code)
{
	errno = exit_code;
	ft_free_sh(sh);
	exit(exit_code);
}

/// @brief			Check if string is a number
/// @param str		String to check
int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

/** @} */
