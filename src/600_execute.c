/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:10:50 by passunca          #+#    #+#             */
/*   Updated: 2024/07/16 15:39:32 by passunca         ###   ########.fr       */
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
static void	ft_check_cmds(t_shell *sh);

/**
* @brief	Execute commands
* @param sh	Pointer to a t_shell struct
* @return	SUCCESS(0)
* @return	FAILURE(1)
*/
int	ft_execute(t_shell *sh)
{
	sh->path = ft_split_path(sh->envp);
	sh->n_pipes = sh->n_cmds - (sh->n_cmds > 0);
	ft_check_cmds(sh);
	if (sh->n_cmds == 1)
	{
		if (ft_exec_one(sh))
			return (FAILURE);
	}
	else if (ft_exec_pipeline(sh))
		return (FAILURE);
	ft_set_termios(STDIN_FILENO, TCSAFLUSH, &sh->termios);
	return (SUCCESS);
}

/// @brief			Extract PATH from envp array
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
		ft_free(to_split);
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

static void	ft_check_cmds(t_shell *sh)
{
	int	i;
	int	type;

	i = 0;
	while (i < sh->n_cmds)
	{
		type = ft_exec_check(sh->cmds[i].argv[0]);
		if (type == CMD_EXEC)
			sh->cmds[i].argv[0] = ft_exec_check_cmd(sh->path,
					sh->cmds[i].argv[0]);
		i++;
	}
}

/** @} */
