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

static int	ft_chdir(t_shell *sh, char *path);
static int	ft_get_prev_dir(char ***env, char *old, char *pwd);
static void	ft_chdir_err(char *path);

/// @brief			Change directory
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Pointer to t_cmd struct
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_cd(t_shell *sh, t_cmd *cmd)
{
	char	*home;
	int		chdir;

	if (cmd->argv[1] == NULL)
	{
		home = ft_get_var("HOME", sh->envp);
		if (home == NULL)
			home = ft_strdup(sh->home);
		chdir = ft_chdir(sh, home);
		ft_free(home);
		return (chdir);
	}
	if (cmd->argv[1][0] == '-' && cmd->argv[1][1] != '\0')
		return (ft_flag_err(cmd->argv[0], cmd->argv[1]));
	if (cmd->argc > 2)
		return (ft_err("bash: cd: too many arguments\n", FAILURE));
	if (cmd->argv[1][0] == '\0')
		return (ft_chdir(sh, cmd->argv[1]));
	return (ft_chdir(sh, cmd->argv[1]));
}

/// @brief			Change directory
/// @param sh		Pointer to a t_shell struct
/// @param path		Directory path
static int	ft_chdir(t_shell *sh, char *path)
{
	char	*pwd;
	char	*old;
	int		chdir_ret;

	old = NULL;
	pwd = ft_get_var("PWD", sh->envp);
	if (path == NULL || pwd == NULL || ft_pwd_invalid(pwd))
		pwd = getcwd(NULL, 0);
	chdir_ret = 0;
	if (ft_strncmp(path, "-", 3) == 0)
		ft_get_prev_dir(&sh->envp, old, pwd);
	else
	{
		old = ft_path_resolve(pwd, path);
		chdir_ret = chdir(old);
		if (chdir_ret == 0)
		{
			ft_set_var("OLDPWD", pwd, &sh->envp);
			ft_set_var("PWD", old, &sh->envp);
		}
	}
	if (chdir_ret == -1 && path[0] != '\0')
		return (ft_chdir_err(path), ft_free(pwd),
			ft_free(old), FAILURE);
	return (ft_free(pwd), ft_free(old), 0);
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
	old = ft_get_var("OLDPWD", *env);
	if (old == NULL)
		old = ft_strdup(pwd);
	chdir_ret = chdir(old);
	if (chdir_ret == 0)
	{
		ft_set_var("OLDPWD", pwd, env);
		ft_set_var("PWD", old, env);
		ft_putendl_fd(old, STDOUT_FILENO);
	}
	ft_free(old);
	return (chdir_ret);
}

/// @brief			Change directory error
/// @param path		Directory path
static void	ft_chdir_err(char *path)
{
	t_stat	sb;
	int		stat_ret;

	ft_memset(&sb, 0, sizeof(t_stat));
	stat_ret = stat(path, &sb);
	if (stat_ret == 0 && (sb.st_mode & __S_IFMT) != __S_IFDIR)
		ft_fprintf(STDOUT_FILENO, "bash: cd: %s: Not a directory\n",
			path);
	if (stat_ret == 0 && (sb.st_mode & __S_IFMT) != __S_IFREG)
		ft_fprintf(STDOUT_FILENO,
			"bash: cd: no permission: permission denied\n");
	if (stat_ret == -1)
		ft_fprintf(STDERR_FILENO, "bash: cd: %s: No such file or directory\n",
			path);
}

/** @} */
