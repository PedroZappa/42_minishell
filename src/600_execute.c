/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:10:50 by passunca          #+#    #+#             */
/*   Updated: 2024/07/10 17:06:46 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup execute Execute
* @{
*
* @brief		Execute commands
* @version		1.0
***/

#include "../inc/minishell.h"

static char	**ft_split_path(char **envp);
static int	ft_path_from_env(char **envp);

/**
* @brief	Execute commands
* @details
* - Get path and split it
* - Execute commands (TODO)
* 	- Handle one command
* 	- Or handle many
* - Flush stdin with termios setter
* @param sh	Pointer to a t_shell struct
* @return	SUCCESS(0)
* @return	FAILURE(1)
* @endcode
*/
int	ft_execute(t_shell *sh)
{
	sh->path = ft_split_path(sh->envp);
	if (ft_exec_one(sh))
		return (FAILURE);
	else if (ft_exec_many(sh))
		return (FAILURE);
	ft_set_termios(STDIN_FILENO, TCSAFLUSH, &sh->termios);
	return (SUCCESS);
}

/// @brief			Extract PATH from envp array
/// @details
/// - Extract PATH from envp
/// - Skip PATH= from envp with pointer arithmetics
/// - Split PATH string on :
/// - Append / to each path
/// - Copy paths to array of paths
/// @param envp		Pointer to array of environment variables
/// @return			SUCCESS(Pointer to array of paths)
///	@return			FAILURE(NULL)
/// @note			Used in ft_execute()
static char	**ft_split_path(char **envp)
{
	char	**path;
	char	*to_split;
	int		i;

	i = ft_path_from_env(envp);
	if (i != -1)
	{
		to_split = ft_strdup(envp[i] + 5);
		path = ft_split(to_split, ':');
		free(to_split);
		i = -1;
		while (path[++i])
			path[i] = ft_strjoin_free(path[i], ft_strdup("/"));
		return (path);
	}
	else
		return (NULL);
}

/// @brief			Extract PATH index from envp array
/// @param envp		Pointer to array of environment variables
/// @return			SUCCESS(PATH index)
/// @return			FAILURE(-1)
static int	ft_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		if (!ft_strncmp("PATH=", envp[i++], 5))
			return (i - 1);
	return (-1);
}

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
