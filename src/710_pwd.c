/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   710_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:12:55 by passunca          #+#    #+#             */
/*   Updated: 2024/07/16 14:25:25 by passunca         ###   ########.fr       */
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
/// @param cmd		Pointer to t_cmd struct
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_pwd(t_shell *sh, t_cmd *cmd)
{
	char	*pwd;
	int		i;

	ft_set_var("_", cmd->argv[0], &sh->envp);
	i = 0;
	while (cmd->argv[++i])
		if (cmd->argv[i][0] == '-')
			return (ft_flag_err(cmd->argv[0], cmd->argv[i]));
	pwd = ft_get_var("PWD", sh->envp, NULL);
	if (pwd == NULL || ft_pwd_invalid(pwd))
		pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	ft_free(pwd);
	return (SUCCESS);
}

/** @} */
