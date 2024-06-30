/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   620_exec_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:51:40 by passunca          #+#    #+#             */
/*   Updated: 2024/06/30 12:14:51 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup exec_one Execute one
* @{
*
* @brief		Execute one command
* @version		1.0
***/

#include "../inc/minishell.h"

int	ft_exec_check(char *cmd);

/// @brief			Execute one command
/// @param sh		Pointer to a t_shell struct
/// @var cmd		Command type
/// @return			SUCCESS(0)
///	@return			FAILURE(1)
/// @details	
/// - Check command type
/// - Execute command
///	@note			Used in ft_execute()
int	ft_exec_one(t_shell *sh)
{
	int	cmd;

	cmd = CMD_EXEC;
	if (sh->cmds[0].argv[0] != NULL)
		cmd = ft_exec_check(sh->cmds[0].argv[0]);
	if (cmd == CMD_EXIT)
		if (ft_exec(sh, cmd, 0))
			return (ft_free_arr(sh->path), FAILURE);
	return (ft_free_arr(sh->path), SUCCESS);
}
