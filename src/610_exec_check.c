/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   610_exec_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:14:42 by passunca          #+#    #+#             */
/*   Updated: 2024/08/09 11:42:10 by gfragoso         ###   ########.fr       */
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
	if (ft_strncmp(cmd, "exit", 5) == SUCCESS)
		type = CMD_EXIT;
	if (ft_strncmp(cmd, "pwd", 4) == SUCCESS)
		type = CMD_PWD;
	if (ft_strncmp(cmd, "cd", 3) == SUCCESS)
		type = CMD_CD;
	if (ft_strncmp(cmd, "env", 4) == SUCCESS)
		type = CMD_ENV;
	if (ft_strncmp(cmd, "clear", 6) == SUCCESS)
		type = CMD_CLEAR;
	if (ft_strncmp(cmd, "echo", 5) == SUCCESS)
		type = CMD_ECHO;
	if (ft_strncmp(cmd, "export", 7) == SUCCESS)
		type = CMD_EXPORT;
	if (ft_strncmp(cmd, "unset", 6) == SUCCESS)
		type = CMD_UNSET;
	return (type);
}

static int	ft_stat_cmd(char *cmd)
{
	t_stat	sb;
	int		stat_ret;

	memset(&sb, 0, sizeof(t_stat));
	stat_ret = stat(cmd, &sb);
	if (stat_ret == -1)
	{
		ft_fprintf(STDERR_FILENO, "bash: %s: No such file or directory\n", cmd);
		g_exit = 127;
		return (FAILURE);
	}
	if ((sb.st_mode & __S_IFMT) != __S_IFREG)
	{
		if ((sb.st_mode & __S_IFMT) == __S_IFDIR)
			ft_fprintf(STDERR_FILENO, "bash: %s: Is a directory\n", cmd);
		else
			ft_fprintf(STDERR_FILENO, "bash: %s: Permission denied\n", cmd);
		g_exit = 126;
		return (FAILURE);
	}
	return (SUCCESS);
}

static char	*ft_stat_path(char **path, char *cmd)
{
	char	*exec_path;
	int		i;

	i = 0;
	while (path && path[i])
	{
		exec_path = ft_strjoin(path[i], cmd);
		if (!exec_path)
			break ;
		if (access(exec_path, F_OK) == 0)
			return (ft_free(cmd), exec_path);
		++i;
		free(exec_path);
	}
	g_exit = ft_cmd_err(cmd, 127);
	return (ft_free(cmd), NULL);
}

char	*ft_exec_check_cmd(char **path, char *cmd)
{
	if (cmd == NULL)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (ft_stat_cmd(cmd))
			return (ft_free(cmd), NULL);
		return (cmd);
	}
	if (path == NULL)
	{
		ft_fprintf(STDERR_FILENO, "bash: %s: No such file or directory\n",
			cmd);
		g_exit = 127;
		return (ft_free(cmd), NULL);
	}
	return (ft_stat_path(path, cmd));
}

/** @} */
