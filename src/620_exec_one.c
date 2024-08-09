/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   620_exec_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:51:40 by passunca          #+#    #+#             */
/*   Updated: 2024/07/16 15:39:56 by passunca         ###   ########.fr       */
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

/// @brief			Execute one command
/// @details
/// - Check command type
/// - Execute command
/// @param sh		Pointer to a t_shell struct
/// @return			SUCCESS(0)
///	@return			FAILURE(1)
///	@note			Used in ft_execute()
int	ft_exec_one(t_shell *sh)
{
	int	cmd;

	cmd = CMD_EXEC;
	if (sh->cmds[0].argv[0])
		cmd = ft_exec_check(sh->cmds[0].argv[0]);
	if ((cmd == CMD_EXIT) || (cmd == CMD_PWD) || (cmd == CMD_PATH)
		|| (cmd == CMD_ENV) || (cmd == CMD_CLEAR) || (cmd == CMD_ECHO)
		|| (cmd == CMD_CD) || ((cmd == CMD_EXPORT) && sh->cmds[0].argv[1])
		|| ((cmd == CMD_UNSET) && sh->cmds[0].argv[1]))
	{
		if (ft_exec(sh, cmd, 0))
			return (ft_free_arr(sh->path), FAILURE);
	}
	else if (ft_exec_fork(sh))
		return (ft_free_arr(sh->path), FAILURE);
	ft_update_last_cmd(sh);
	return (ft_free_arr(sh->path), SUCCESS);
}

/// @brief			Execute one command as a child process
/// @details
/// - Set signal handlers in parent process
/// - Fork a child process:
///		- Set signal handlers
///		- Execute command
///	- Wait for child process
///	- Handle exit status
///		- If program was terminated by signal: Return the signal number
///		- Else check if program exited: Return exit status
/// @param sh		Pointer to a t_shell struct
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_exec_fork(t_shell *sh)
{
	pid_t	pid;

	if (sh->cmds[0].in.flag == IGNORE_SIGQUIT)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, ft_fork_sighandler);
	signal(SIGINT, ft_fork_sighandler);
	pid = fork();
	if (pid == PID_FAIL)
		return (ft_err(FORK_ERR, errno), FAILURE);
	if (pid == SUCCESS)
	{
		ft_fork_sigset();
		ft_exec_child(sh, NULL);
	}
	wait(&g_exit);
	if (WIFSIGNALED(g_exit))
		g_exit = (128 + WTERMSIG(g_exit));
	else if (WIFEXITED(g_exit))
		g_exit = WEXITSTATUS(g_exit);
	return (SUCCESS);
}

/** @} */
