/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:10:50 by passunca          #+#    #+#             */
/*   Updated: 2024/06/20 18:41:37 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @file			600_execute.c
* @brief		Execute commands
* @version		1.0
* @author		passunca
***/

#include "../inc/minishell.h"

static char	**ft_split_path(char **envp);
static int	ft_path_from_env(char **envp);

/// @brief			Execute commands
/// @param sh		Pointer to a t_shell struct
/// @return			0 on success, 1 on failure.
/// @details		- Get path and split it
///					- Execute commands (TODO)
///						- Handle one command
///						- Or handle many
///					- Flush stdin with termios setter
int	ft_execute(t_shell *sh)
{
	sh->path = ft_split_path(sh->envp);
	ft_set_termios(STDIN_FILENO, TCSAFLUSH, &sh->termios);
	return (SUCCESS);
}

/// @brief			Extract PATH from envp array
/// @param envp		Pointer to array of environment variables
/// @var path		Pointer to array of paths
/// @var to_split	Pointer to temporary string
/// @var i			PATH indexer
/// @return			SUCCESS(Pointer to array of paths) or FAILURE(NULL)
/// @details		- Extract PATH from envp
/// 				- Skip PATH= from envp with pointer arithmetics
/// 				- Split PATH string on :
/// 				- Append / to each path
/// 				- Copy paths to array of paths
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

/// @brief			Extract PATH index in envp array
/// @param envp		Pointer to array of environment variables
/// @return			SUCCESS(PATH index) or FAILURE(-1)
static int	ft_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		if (!ft_strncmp("PATH=", envp[i++], 5))
			return (i);
	return (-1);
}
