/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   770_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:37:35 by passunca          #+#    #+#             */
/*   Updated: 2024/07/09 21:20:05 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief			Unset built-in
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_unset(t_shell *sh, int n)
{
	char	*var;
	int	i;

	ft_set_var(sh->cmds[n].argv[sh->cmds[n].argc - 1], "_", &sh->envp);
	if (!sh->cmds[n].argv[1] || !sh->envp)
		return (FAILURE);
	while (sh->cmds[n].argv[++i])
		if (sh->cmds[n].argv[i][0] == '-')
			return (ft_flag_err(sh->cmds[n].argv[0], sh->cmds[n].argv[1], 1));
	i = 0;
	while (sh->cmds[n].argv[++i])
	{
		var = sh->cmds[n].argv[i];
		if (!ft_strchr(var, '='))
		{
			if (ft_get_var_index(var, sh->envp) >= 0)
				sh->envp = ft_env_del_var(sh->envp, var);
			if (ft_get_var_index(var, sh->envt) >= 0)
				sh->envp = ft_env_del_var(sh->envt, var);
		}
	}
	return (SUCCESS);
}
