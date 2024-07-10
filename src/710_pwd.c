/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   710_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:12:55 by passunca          #+#    #+#             */
/*   Updated: 2024/07/03 12:01:34 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup 	pwd		pwd built-in command
* @{
*
* @brief		pwd built-in command
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			pwd built-in command
/// @details
/// - Check if command flags are valid
/// - Get current working directory
/// - Print directory
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_pwd(t_shell *sh, int n)
{
	char	*pwd;
	int		i;

	ft_set_var("_", sh->cmds[n].argv[sh->cmds[n].argc - 1], &sh->envp);
	i = 0;
	while (sh->cmds[n].argv[++i])
		if (sh->cmds[n].argv[i][0] == '-')
			return (ft_flag_err(sh->cmds[n].argv[0], sh->cmds[n].argv[i], 1));
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		free(pwd);
		pwd = ft_get_var("PWD", sh->envp, NULL);
		ft_putendl_fd(pwd, STDOUT_FILENO);
		return (SUCCESS);
	}
	else
		ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (SUCCESS);
}

/** @} */
