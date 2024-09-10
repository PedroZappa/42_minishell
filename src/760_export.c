/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   760_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:05:04 by passunca          #+#    #+#             */
/*   Updated: 2024/07/16 15:28:27 by passunca         ###   ########.fr       */
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
static void	ft_update_var(t_shell *sh, t_cmd *cmd, int i);
static void	ft_export_var(t_shell *sh, t_cmd *cmd, int i);
static void	ft_export_prc(t_shell *sh, t_cmd *cmd, int i, int *exit);

/// @brief		Export environment variables built-in
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Pointer to t_cmd struct
int	ft_export(t_shell *sh, t_cmd *cmd)
{
	int	i;
	int	exit;

	if (!sh->envp || !cmd->argv[1] || !cmd->argv[1][0])
		return (ft_export_status(sh, cmd));
	ft_append(sh, cmd, 1);
	exit = 0;
	i = 0;
	while (cmd->argv[++i])
	{
		if (cmd->argv[i][0] == '-')
			return (ft_flag_err(cmd->argv[0], cmd->argv[i]));
		ft_export_prc(sh, cmd, i, &exit);
	}
	return (exit);
}

static void	ft_export_prc(t_shell *sh, t_cmd *cmd, int i, int *exit)
{
	if (ft_isvalid_var(cmd->argv[i]) == FAILURE)
	{
		*exit = 1;
		ft_fprintf(STDERR_FILENO,
			"bash: %s: '%s': not a valid identifier\n",
			cmd->argv[0], cmd->argv[i]);
		return ;
	}
	if (ft_strchr(cmd->argv[i], '='))
		ft_update_var(sh, cmd, i);
	else
		ft_export_var(sh, cmd, i);
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
/// @param cmd		Pointer to t_cmd struct
/// @param i	Argument index to start from
static void	ft_update_var(t_shell *sh, t_cmd *cmd, int i)
{
	int		key_len;
	char	*key;
	char	*value;

	key_len = (ft_strlen(cmd->argv[i])
			- ft_strlen(ft_strchr(cmd->argv[i], '=')));
	key = ft_substr(cmd->argv[i], 0, key_len);
	value = ft_strdup(ft_strchr(cmd->argv[i], '=') + 1);
	ft_set_var(key, value, &sh->envp);
	ft_free(key);
	ft_free(value);
}

/// @brief		Export new variable
/// @param sh	Pointer to a t_shell struct
/// @param cmd		Pointer to t_cmd struct
/// @param i	Argument index to start from
static void	ft_export_var(t_shell *sh, t_cmd *cmd, int i)
{
	char	*key;
	char	*value;
	int		j;

	key = cmd->argv[i];
	j = ft_get_var_index(key, sh->envp);
	if (j >= 0)
		return ;
	ft_set_var(key, NULL, &sh->envp);
}

/** @} */
