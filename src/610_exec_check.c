/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   610_exec_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:14:42 by passunca          #+#    #+#             */
/*   Updated: 2024/07/10 17:06:07 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup 	exec_check Execute
* @{
*
* @brief		Check command type
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			Check command type
/// @param cmd		Command name
/// @return			SUCCESS(cmd type)
/// @note			Used in ft_exec_one()
int	ft_exec_check(char *cmd)
{
	int	type;

	type = CMD_EXEC;
	if (ft_strncmp(cmd, "exit", 4) == SUCCESS)
		type = CMD_EXIT;
	if (ft_strncmp(cmd, "pwd", 3) == SUCCESS)
		type = CMD_PWD;
	if (ft_strncmp(cmd, "cd", 2) == SUCCESS)
		type = CMD_CD;
	if (ft_strncmp(cmd, "env", 3) == SUCCESS)
		type = CMD_ENV;
	if (ft_strncmp(cmd, "clear", 5) == SUCCESS)
		type = CMD_CLEAR;
	if (ft_strncmp(cmd, "echo", 4) == SUCCESS)
		type = CMD_ECHO;
	if (ft_strncmp(cmd, "export", 6) == SUCCESS)
		type = CMD_EXPORT;
	if (ft_strncmp(cmd, "unset", 5) == SUCCESS)
		type = CMD_UNSET;
	return (type);
}

/** @} */
