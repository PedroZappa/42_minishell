/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   770_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:37:35 by passunca          #+#    #+#             */
/*   Updated: 2024/07/16 14:40:31 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @defgroup env_set Set environment variable
* @{
*
* @brief		Set environment variable
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			Unset built-in
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Pointer to t_cmd struct
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_unset(t_shell *sh, t_cmd *cmd)
{
	char	*var;
	int		i;

	ft_set_var("_", cmd->argv[0], &sh->envp);
	i = 0;
	if (!cmd->argv[1] || !sh->envp)
		return (FAILURE);
	while (cmd->argv[++i])
		if (cmd->argv[i][0] == '-')
			return (ft_flag_err(cmd->argv[0], cmd->argv[i]));
	i = 0;
	while (cmd->argv[++i])
	{
		var = cmd->argv[i];
		if (ft_strchr(var, '=') == NULL)
			if (ft_get_var_index(var, sh->envp) >= 0)
				sh->envp = ft_env_del_var(sh->envp, var);
	}
	return (SUCCESS);
}

/** @} */
