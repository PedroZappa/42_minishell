/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   730_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:05:44 by passunca          #+#    #+#             */
/*   Updated: 2024/07/16 14:24:23 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup 	env		env built-in
* @{
*
* @brief		Env built-in
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			Env built-in
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Pointer to t_cmd struct
/// @return			SUCCESS(i)
/// @return			FAILURE(1)
int	ft_env(t_shell *sh, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->argv[++i])
		if (cmd->argv[i][0] == '-')
			return (ft_flag_err(cmd->argv[0], cmd->argv[1]));
	i = -1;
	while (sh->envp[++i])
		if (ft_strchr(sh->envp[i], '='))
			ft_fprintf(STDOUT_FILENO, "%s\n", sh->envp[i]);
	return (0);
}

/** @} */
