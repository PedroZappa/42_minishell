/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   730_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:05:44 by passunca          #+#    #+#             */
/*   Updated: 2024/07/07 11:55:00 by passunca         ###   ########.fr       */
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
/// @details
/// - If command has options or flags return error
/// - Print environment variables
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
/// @return			SUCCESS(env_i)
///	@note			Used in ft_execute()
int	ft_env(t_shell *sh, int n)
{
	int	env_i;
	int	i;

	ft_set_var("env", "_", &sh->envp);
	i = 0;
	while (sh->cmds[n].argv[++i])
		if (sh->cmds[n].argv[i][0] == '-')
			return (ft_flag_err(sh->cmds[n].argv[0], sh->cmds[n].argv[i], 1));
	env_i = 0;
	while (sh->envp[env_i])
	{
		if (ft_strchr(sh->envp[env_i], '='))
			ft_putendl_fd(sh->envp[env_i++], STDOUT_FILENO);
		++env_i;
	}
	return (env_i);
}

/** @} */
