/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   650_exec_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:13:26 by passunca          #+#    #+#             */
/*   Updated: 2024/07/16 15:14:07 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup 	650_exec_cmd	Execute commands
* @{
*
* @brief		Execute commands
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			Execute a command
/// @details
/// - Set statbuf to 0
/// - If command type is CMD_EXEC
/// 	- Execute command
/// - Else
/// 	- Execute builtin
/// @param sh		Pointer to a t_shell struct
/// @param id		Command type
/// @param i		Command index
/// @note			Used in ft_exec_child()
void	ft_exec_cmd(t_shell *sh, int id, int i)
{
	t_stat	statbuf;

	memset(&statbuf, 0, sizeof(t_stat));
	if (id == CMD_EXEC)
	{
		if (!sh->cmds[i].argv[0][0])
			return ;
		if (stat(sh->cmds[i].argv[0], &statbuf) < 0)
			errno = ENOENT;
		ft_execve(sh->path, sh->cmds[i].argv, sh->envp);
		// TODO: Handle errors
		ft_free_sh(sh);
		exit(CMD_NOT_FOUND);
	}
	else
		ft_exec(sh, id, i);
}

/// @brief			Execute one builtin command
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Command type
/// @param n		Command index (to handle multiple commands)
/// @return			SUCCESS(0)
///	@return			FAILURE(1)
///	@note			Used in ft_execute()
int	ft_exec(t_shell *sh, int cmd, int n)
{
	if (cmd == CMD_EXIT)
		return (ft_exit(sh, n));
	if (cmd == CMD_PWD)
		g_exit = ft_pwd(sh, n);
	if (cmd == CMD_CD)
		g_exit = ft_cd(sh, n);
	if (cmd == CMD_ENV)
		g_exit = ft_env(sh, n);
	if (cmd == CMD_CLEAR)
		g_exit = ft_clear(n);
	if (cmd == CMD_ECHO)
		g_exit = ft_echo(sh, n);
	if (cmd == CMD_EXPORT)
		g_exit = ft_export(sh, n);
	if (cmd == CMD_UNSET)
		g_exit = ft_unset(sh, n);
	return (SUCCESS);
}

/** @} */
