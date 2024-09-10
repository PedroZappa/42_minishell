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

static void	ft_append_var(t_shell *sh, t_cmd *cmd, int i);

/// @brief			Build array of environment variables
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Pointer to t_cmd struct
int	ft_append(t_shell *sh, t_cmd *cmd, int i)
{
	if (!sh->envp || !cmd->argv[0])
		return (ft_err(ENV_INIT_ERR, FAILURE));
	while (cmd->argv[i])
	{
		if ((ft_strchr(cmd->argv[i], '+')
				&& ft_strchr(cmd->argv[i], '='))
			&& (ft_strchr(cmd->argv[i], '=')
				- ft_strchr(cmd->argv[i], '+') == 1))
			ft_append_var(sh, cmd, i);
		++i;
	}
	return (SUCCESS);
}

/// @brief			Append value to variable key
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Pointer to t_cmd struct
/// @param i		Argument index to start from
static void	ft_append_var(t_shell *sh, t_cmd *cmd, int i)
{
	char	*key;
	char	*new_val;
	char	*old_val;
	char	*plus_pos;
	int		key_len;

	plus_pos = ft_strchr(cmd->argv[i], '+');
	key_len = (ft_strlen(cmd->argv[i]) - ft_strlen(plus_pos));
	key = ft_substr(cmd->argv[i], 0, key_len);
	new_val = ft_strdup(ft_strchr(cmd->argv[i], '=') + 1);
	old_val = ft_get_var(key, sh->envp);
	if (!old_val)
		old_val = ft_strdup("");
	ft_free(cmd->argv[i]);
	cmd->argv[i] = ft_strjoin_free(
			ft_strjoin_free(key, ft_strdup("=")),
			ft_strjoin_free(old_val, new_val));
}

/** @} */
