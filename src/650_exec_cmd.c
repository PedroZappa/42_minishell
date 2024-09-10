/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   650_exec_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:13:26 by passunca          #+#    #+#             */
/*   Updated: 2024/09/09 09:13:37 by passunca         ###   ########.fr       */
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
/// @param sh		Pointer to a t_shell struct
/// @param id		Command type
/// @param i		Command index
/// @note			Used in ft_exec_child()
void	ft_exec_cmd(t_shell *sh, int id, int i)
{
	if (id != CMD_EXEC)
	{
		ft_exec(sh, id, i);
		return ;
	}
	if (!sh->cmds[i].argv[0][0])
		return ;
	ft_execve(sh->path, sh->cmds[i].argv, sh->envp);
	ft_free_sh(sh);
	exit(g_exit);
}

/// @brief			Execute one builtin command
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Command type
/// @param n		Command index (to handle multiple commands)
/// @return			SUCCESS(0)
///	@return			FAILURE(1)
///	@note			Used in ft_execute()
int	ft_exec(t_shell *sh, int type, int n)
{
	t_cmd	*cmd;

	cmd = sh->cmds + n;
	if (type == CMD_EXIT)
		return (ft_exit(sh, cmd));
	if (type == CMD_PWD)
		g_exit = ft_pwd(sh, cmd);
	if (type == CMD_CD)
		g_exit = ft_cd(sh, cmd);
	if (type == CMD_ENV)
		g_exit = ft_env(sh, cmd);
	if (type == CMD_CLEAR)
		g_exit = ft_clear();
	if (type == CMD_ECHO)
		g_exit = ft_echo(sh, cmd);
	if (type == CMD_EXPORT)
		g_exit = ft_export(sh, cmd);
	if (type == CMD_UNSET)
		g_exit = ft_unset(sh, cmd);
	return (SUCCESS);
}

/** @} */
