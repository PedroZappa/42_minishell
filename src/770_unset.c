/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   770_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:37:35 by passunca          #+#    #+#             */
/*   Updated: 2024/07/09 16:50:51 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_unset(t_shell *sh, int n)
{
	char	*var;
	int	i;

	ft_set_var(sh->cmds[n].argv[sh->cmds[n].argc - 1], "_", &sh->envp);
	if (!sh->cmds[n].argv[1] || !sh->envp)
		return (FAILURE);
	if (sh->cmds[n].argv[1])
		return (ft_flag_err(sh->cmds[n].argv[0], sh->cmds[n].argv[1], 1));
	i = 0;
	while (sh->cmds[n].argv[++i])
	{
		var = sh->cmds[n].argv[i];
		if (!ft_strchr(var, '='))
		{
			// TODO: ft_get_var_index() from envp, implement ft_env_del_var()
			// TODO: ft_get_var_index() from envt
		}
	}
	return (SUCCESS);
}
