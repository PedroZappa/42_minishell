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
/// @param cmd		Command
/// @note			Used in ft_exec_child()
void	ft_exec_cmd(t_shell *sh, t_cmd *cmd)
{
	int	id;

	id = ft_exec_check(cmd->argv[0]);
	if (id != CMD_EXEC)
	{
		ft_exec(sh, cmd, id);
		return ;
	}
	if (!cmd->argv[0][0])
		return ;
	ft_execve(cmd, sh->envp);
	ft_free_sh(sh);
	exit(g_exit);
}

/// @brief			Execute one builtin command
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Command
/// @param type		Base command type
/// @return			SUCCESS(0)
///	@return			FAILURE(1)
///	@note			Used in ft_execute()
int	ft_exec(t_shell *sh, t_cmd *cmd, int type)
{
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

/// @brief			Execute command with execve w/ absolute or relative path
/// @param cmd		Pointer to command
/// @param envp		Pointer to environment variables array
void	ft_execve(t_cmd *cmd, char **envp)
{
	int	execve_err;

	execve_err = execve(cmd->argv[0], cmd->argv, envp);
	if (execve_err == EXECVE_ERR)
	{
		if (access(cmd->cmd, X_OK))
		{
			ft_fprintf(STDERR_FILENO,
				"bash: %s: Permission denied\n", cmd->cmd);
			g_exit = 126;
		}
		else
		{
			ft_fprintf(STDERR_FILENO,
				"bash: %s: File could not be executed\n", cmd->cmd);
			g_exit = errno;
		}
	}
}

/** @} */
