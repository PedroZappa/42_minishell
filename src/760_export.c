/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   760_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:05:04 by passunca          #+#    #+#             */
/*   Updated: 2024/07/11 10:54:22 by passunca         ###   ########.fr       */
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

static int	ft_export_status(t_shell *sh, int n);
static char	**ft_sort_env(char **env, int n);

/// @brief		Export environment variables built-in
/// @details
/// - Set environment variable "_"
///
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
int	ft_export(t_shell *sh, int n)
{
	if (!sh->envp || !sh->cmds[n].argv[1] || !sh->cmds[n].argv[1][0])
		return (ft_export_status(sh, n));
	ft_build_var(sh, n, 1);
	return (SUCCESS);
}

/// @brief		Export environment variables
/// @details
/// - Check if command has argument
///		- Initialize a copy of envp
///		- Sort envp
///		- Print sorted envp vars if key has value
///	- Else print syntax error
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
static int	ft_export_status(t_shell *sh, int n)
{
	char	**sorted;
	char	*equal;
	int		i;

	i = 0;
	if (!sh->cmds[n].argv[1])
	{
		if (!sh->envp)
			return (ft_err(ENV_INIT_ERR, FAILURE));
		sorted = ft_init_env(sh->envp);
		sorted = ft_sort_env(sorted, 0);
		i = -1;
		while (sorted[++i])
		{
			equal = ft_strchr(sorted[i], '=');
			if (equal && *(equal + 1))
				ft_fprintf(STDOUT_FILENO, "declare -x %s\n", sorted[i]);
		}
		ft_free_arr(sorted);
	}
	else if (sh->cmds[n].argv[1][0] == '\0')
		return (ft_err(SYNTAX_ERR, FAILURE));
	return (SUCCESS);
}

/// @brief			Sort array of environment variables
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
static char	**ft_sort_env(char **env, int n)
{
	int	ret;
	int	var_len;
	int	next_len;
	int	i;
	int	j;

	while (env[n] && env[n + 1])
	{
		j = n;
		i = j;
		while (env[++j])
		{
			var_len = (ft_strchr(env[i], '=') - env[i]);
			next_len = (ft_strchr(env[j], '=') - env[j]);
			ret = ft_strncmp(env[i], env[j], ft_min(var_len, next_len));
			if ((ret > 0) || ((ret == 0) && (var_len > next_len)))
				i = j;
		}
		ft_swapstrs(&env[n++], &env[i]);
	}
	return (env);
}

/** @} */
