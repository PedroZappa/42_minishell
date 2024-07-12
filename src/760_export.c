/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   760_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:05:04 by passunca          #+#    #+#             */
/*   Updated: 2024/07/11 16:34:09 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup export Export builtin
* @{
*
* @brief		Export environment variables built-in
* @version		1.0
***/

#include "../inc/minishell.h"

static int	ft_isvalid_var(char *var);
static void	ft_update_var(t_shell *sh, int n, int i);
static void	ft_export_var(t_shell *sh, int n, int i);

/// @brief		Export environment variables built-in
/// @details
/// - Set environment variable "_"
///
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
int	ft_export(t_shell *sh, int n)
{
	int	i;

	if (!sh->envp || !sh->cmds[n].argv[1] || !sh->cmds[n].argv[1][0])
		return (ft_export_status(sh, n));
	ft_build_var(sh, n, 1);
	i = 0;
	while (sh->cmds[n].argv[++i])
	{
		if (sh->cmds[n].argv[i][0] == '-')
			return (ft_flag_err(sh->cmds[n].argv[0], sh->cmds[n].argv[i], 1));
		if (ft_isvalid_var(sh->cmds[n].argv[i]) == FAILURE)
			return (ft_fprintf(STDERR_FILENO,
					"bash: %s: '%s': not a valid identifier\n",
					sh->cmds[n].argv[0], sh->cmds[n].argv[i]), FAILURE);
		else
		{
			if (ft_strchr(sh->cmds[n].argv[i], '='))
				ft_update_var(sh, n, i);
			else
				ft_export_var(sh, n, i);
		}
	}
	return (SUCCESS);
}

/// @brief		Check if variable is valid
/// @param var	Variable to check
/// @return		SUCCESS(0)
/// @return		FAILURE(1)
static int	ft_isvalid_var(char *var)
{
	int	i;

	if (*var && (!ft_isalpha(*var) || (*var == '_')))
		return (FAILURE);
	i = -1;
	while (var[++i] && (var[i] != '=') && (var[i] != '+'))
		if (!ft_isalnum(var[i]) && (var[i] != '_'))
			return (FAILURE);
	return (SUCCESS);
}

/// @brief		Update variable
/// @param sh	Pointer to a t_shell struct
/// @param n	Command index
/// @param i	Argument index to start from
static void	ft_update_var(t_shell *sh, int n, int i)
{
	int		key_len;
	char	*key;
	char	*value;

	key_len = (ft_strlen(sh->cmds[n].argv[i])
			- ft_strlen(ft_strchr(sh->cmds[n].argv[i], '=')));
	key = ft_substr(sh->cmds[n].argv[i], 0, key_len);
	value = ft_strdup(ft_strchr(sh->cmds[n].argv[i], '=') + 1);
	ft_set_var(key, value, &sh->envp);
	if (ft_get_var_index(key, sh->envt) >= 0)
		sh->envt = ft_env_del_var(sh->envt, key);
	ft_free(key);
	ft_free(value);
}

/// @brief		Export new variable
/// @param sh	Pointer to a t_shell struct
/// @param n	Command index
/// @param i	Argument index to start from
static void	ft_export_var(t_shell *sh, int n, int i)
{
	char	*key;
	char	*value;
	int		j;

	key = sh->cmds[n].argv[i];
	j = ft_get_var_index(key, sh->envp);
	if (j >= 0)
		return ;
	j = ft_get_var_index(key, sh->envt);
	if (!j)
		ft_set_var(key, NULL, &sh->envp);
	else
	{
		value = ft_get_var(key, NULL, sh->envt);
		ft_set_var(key, value, &sh->envp);
		sh->envt = ft_env_del_var(sh->envt, key);
		ft_free(value);
	}
}

/** @} */
