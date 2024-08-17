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
/// @param n		Command index
/// @return			SUCCESS(i)
/// @return			FAILURE(1)
///	@note			Used in ft_execute()
int	ft_env(t_shell *sh, int n)
{
	char	*equal;
	int		i;

	ft_set_var("_", sh->cmds[n].argv[0], &sh->envp);
	i = 0;
	while (sh->cmds[n].argv[++i])
		if (sh->cmds[n].argv[i][0] == '-')
			return (ft_flag_err(sh->cmds[n].argv[0], sh->cmds[n].argv[1], 1));
	i = -1;
	while (sh->envp[++i])
	{
		equal = ft_strchr(sh->envp[i], '=');
		if (!equal)
			return (i);
		if (equal && *(equal + 1) != '\0')
			ft_fprintf(STDOUT_FILENO, "%s\n", sh->envp[i]);
	}
	return (i);
}

/** @} */
