/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   720_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 08:19:31 by passunca          #+#    #+#             */
/*   Updated: 2024/08/08 12:33:16 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @defgroup 	cd Change directory
* @{
*
* @brief		Change directory
* @version		1.0
***/

#include "../inc/minishell.h"

static int	ft_chdir(char ***env, char *path);
static int	ft_get_prev_dir(char ***env, char *old, char *pwd);

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

	ft_set_var("_", sh->cmds[cmd_n].argv[0], &sh->envp);
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
	char	*old;
	int		chdir_ret;

	pwd = NULL;
	old = NULL;
	pwd = getcwd(NULL, 0);
	chdir_ret = 0;
	if (path[0] == '-')
		ft_get_prev_dir(env, old, pwd);
	else
	{
		chdir_ret = chdir(path);
		ft_set_var("OLDPWD", pwd, env);
		ft_free(old);
		old = getcwd(NULL, 0);
		ft_set_var("PWD", old, env);
	}
	if (chdir_ret == -1)
	{
		ft_fprintf(STDERR_FILENO,
			"bash: %s: No such file or directory\n", path);
		return (ft_free(old), FAILURE);
	}
	return (ft_free(pwd), ft_free(old), chdir_ret);
}

/// @brief			Get previous directory
/// @param env		Pointer to array of environment variables
/// @param old		Pointer to old directory
/// @param pwd		Pointer to current directory
/// @return			SUCCESS(chdir_ret)
int	ft_get_prev_dir(char ***env, char *old, char *pwd)
{
	int		chdir_ret;

	chdir_ret = 0;
	old = ft_get_var("OLDPWD", *env, NULL);
	ft_set_var("OLDPWD", pwd, env);
	if (old == NULL)
		old = pwd;
	ft_set_var("PWD", old, env);
	ft_putendl_fd(old, STDOUT_FILENO);
	chdir_ret = chdir(old);
	return (chdir_ret);
}

/** @} */
