/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   520_build_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:53:17 by passunca          #+#    #+#             */
/*   Updated: 2024/07/11 10:55:10 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup build_var Append string to variable
* @{
*
* @brief		Build environment variable
* @version		1.0
***/

#include "../inc/minishell.h"

static void	ft_append_var(t_shell *sh, int n, int i);

/// @brief			Build array of environment variables
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
int	ft_append(t_shell *sh, int n, int i)
{
	if (!sh->envp || !sh->cmds[n].argv[0])
		return (ft_err(ENV_INIT_ERR, FAILURE));
	while (sh->cmds[n].argv[i])
	{
		if ((ft_strchr(sh->cmds[n].argv[i], '+')
				&& ft_strchr(sh->cmds[n].argv[i], '='))
			&& (ft_strchr(sh->cmds[n].argv[i], '=')
				- ft_strchr(sh->cmds[n].argv[i], '+') == 1))
			ft_append_var(sh, n, i);
		++i;
	}
	return (SUCCESS);
}

/// @brief			Append value to variable key
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
/// @param i		Argument index to start from
static void	ft_append_var(t_shell *sh, int n, int i)
{
	char	*key;
	char	*new_val;
	char	*old_val;
	char	*plus_pos;
	int		key_len;

	plus_pos = ft_strchr(sh->cmds[n].argv[i], '+');
	key_len = (ft_strlen(sh->cmds[n].argv[i]) - ft_strlen(plus_pos));
	key = ft_substr(sh->cmds[n].argv[i], 0, key_len);
	new_val = ft_strdup(ft_strchr(sh->cmds[n].argv[i], '=') + 1);
	old_val = ft_get_var(key, sh->envp, sh->envt);
	if (!old_val)
		old_val = ft_strdup("");
	ft_free(sh->cmds[n].argv[i]);
	sh->cmds[n].argv[i] = ft_strjoin_free(
			ft_strjoin_free(key, ft_strdup("=")),
			ft_strjoin_free(old_val, new_val));
}

/** @} */
