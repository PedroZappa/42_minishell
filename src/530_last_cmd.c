/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   530_last_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:19:46 by passunca          #+#    #+#             */
/*   Updated: 2024/07/16 14:42:19 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup last_cmd	Handle _ environment variable
* @{
*
* @brief		Set environment variable
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			Build last command
void	ft_build_last_cmd(t_shell *sh, int n)
{
	char	*exec_path;
	int		i;

	if (sh->cmds[n].argv[0])
	{
		i = -1;
		while (sh->path[++i])
		{
			exec_path = ft_strjoin(sh->path[i],
					sh->cmds[n].argv[sh->cmds[n].argc]);
			if (exec_path)
			{
				if (access(exec_path, X_OK) == 0)
				{
					ft_set_var("_", exec_path, &sh->envp);
					ft_free(sh->cmds[n].argv[0]);
					sh->cmds[n].argv[0] = exec_path;
					break ;
				}
				ft_free(exec_path);
			}
		}
	}
	else
		ft_set_var("_", sh->cmds[n].argv[sh->cmds[n].argc], &sh->envp);
}

/// @brief			Update '_' variable (last argument)
/// @details
/// - Check for non-empty argument
/// - Set '_' variable
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
/// @return			SUCCESS(0)
/// @note			Used in ft_exec_one()
int	ft_update_last_cmd(t_shell *sh)
{
	int	i;

	i = (sh->cmds[0].argc);
	while ((i > 0) && (!ft_strncmp(sh->cmds[0].argv[i], "", 1)))
		--i;
	if (i > 0)
		ft_set_var("_", sh->cmds[0].argv[i], &sh->envp);
	return (SUCCESS);
}

/** @} */
