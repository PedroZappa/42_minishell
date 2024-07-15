/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   730_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:05:44 by passunca          #+#    #+#             */
/*   Updated: 2024/07/13 09:48:39 by passunca         ###   ########.fr       */
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
/// @return			SUCCESS(i)
/// @return			FAILURE(1)
///	@note			Used in ft_execute()
int	ft_env(t_shell *sh, int n)
{
	char	*equal;
	int		i;

	ft_build_last_cmd(sh, n);
	if (sh->cmds[n].argv[1])
		return (ft_flag_err(sh->cmds[n].argv[0], sh->cmds[n].argv[1], 1));
	i = -1;
	while (sh->envp[++i])
	{
		equal = ft_strchr(sh->envp[i], '=');
		if (!equal)
			return (i);
		if (equal && *(equal + 1) != '\0')
			ft_putendl_fd(sh->envp[i], STDOUT_FILENO);
	}
	return (i);
}

/** @} */
