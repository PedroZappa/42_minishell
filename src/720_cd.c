/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   720_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 08:19:31 by passunca          #+#    #+#             */
/*   Updated: 2024/07/07 10:58:58 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup 	readline Readline
* @{
*
* @brief		Readline functionality
* @version		1.0
***/

# include "../inc/minishell.h"
#include <unistd.h>

static int	ft_chdir(char ***env, char *path);

/// @brief			Change directory
/// @details
/// - Set variable "_" to the last argument of the command
/// - If no argument: Go to home
///	- If there is more than one argument: Print error message
///	- If argument is empty: Go to home
///	- Change to requested directory
/// @param sh		Pointer to a t_shell struct
/// @param cmd_n	Command index
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_cd(t_shell *sh, int cmd_n)
{
	char	*home;
	int		chdir;

	ft_set_var(sh->cmds[cmd_n].argv[sh->cmds[cmd_n].argc - 1], "_", &sh->envp);
	if (!sh->cmds->argv[1])
	{
		home = ft_get_var("HOME", sh->envp, NULL);
		if (!home)
			return (ft_err(ENV_VAR_ERR, FAILURE));
		chdir = ft_chdir(&sh->envp, home);
		ft_free(home);
		return (chdir);
	}
	if (sh->cmds[cmd_n].argc > 2)
		return (ft_err(ARG_ERR, FAILURE));
	if (sh->cmds[cmd_n].argv[1][0] == '\0')
		return (ft_chdir(&sh->envp, sh->cmds[cmd_n].argv[1]));
	return (ft_chdir(&sh->envp, sh->cmds->argv[1]));
}

static int	ft_chdir(char ***env, char *path)
{
	char	*pwd;
	int		chdir_ret;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	chdir_ret = chdir(path);
	if (chdir_ret == -1)
	{
		ft_free(pwd);
		ft_fprintf(STDERR_FILENO, "cd: %s: No such file or directory\n", path);
		return (FAILURE);
	}
	ft_set_var(path, "OLDPWD", env);
	ft_free(pwd);
	pwd = NULL;
	pwd = getcwd(NULL, 0);
	ft_set_var(pwd, "PWD", env);
	ft_free(pwd);
	return (chdir_ret);
}

/** @} */
