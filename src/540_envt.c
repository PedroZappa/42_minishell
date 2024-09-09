/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   540_envt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:01:26 by passunca          #+#    #+#             */
/*   Updated: 2024/09/09 09:35:23 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_envt(t_shell *sh, t_cmd *cmd)
{
	char	*key;
	char 	*val;
	char	*eq_pos;
	int		key_len;
	int		val_len;

	if (!sh->envt || !cmd->argv[1] || !cmd->argv[1][0])
		return (FAILURE);
	eq_pos = ft_strchr(cmd->argv[1], '=');
	key_len = (ft_strlen(cmd->argv[1]) - ft_strlen(eq_pos) - 1);
	val_len = (ft_strlen(eq_pos) + 1);
	key = ft_substr(cmd->argv[1], 0, key_len);
	val = ft_substr(eq_pos + 1, (eq_pos - cmd->argv[1]), val_len);
	ft_set_var(key, val, &sh->envt);
	ft_free(key);
	ft_free(val);
	return (SUCCESS);
}
