/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   761_export_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:52:07 by passunca          #+#    #+#             */
/*   Updated: 2024/07/11 16:03:21 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup export Export status
* @{
*
* @brief		Export environment variables status
* @version		1.0
***/

#include "../inc/minishell.h"

static char	**ft_sort_env(char **env, int n);
static void	ft_print_export(char *var);

/// @brief		Export environment variables
/// @param sh		Pointer to a t_shell struct
/// @param cmd		Pointer to t_cmd struct
int	ft_export_status(t_shell *sh, t_cmd *cmd)
{
	char	**sorted;
	int		i;

	i = 0;
	if (!cmd->argv[1])
	{
		if (!sh->envp)
			return (ft_err(ENV_INIT_ERR, FAILURE));
		sorted = ft_init_env(sh->envp);
		sorted = ft_sort_env(sorted, 0);
		i = -1;
		while (sorted[++i])
			ft_print_export(sorted[i]);
		ft_free_arr(sorted);
	}
	else if (cmd->argv[1][0] == '\0')
		return (ft_err(SYNTAX_ERR, FAILURE));
	return (SUCCESS);
}

/// @brief			Select Sort array of environment variables
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
static char	**ft_sort_env(char **env, int n)
{
	int	ret;
	int	key_len;
	int	next_len;
	int	min;
	int	next;

	while (env[n] && env[n + 1])
	{
		next = n;
		min = next;
		while (env[++next])
		{
			key_len = (ft_strchr(env[min], '=') - env[min]);
			next_len = (ft_strchr(env[next], '=') - env[next]);
			ret = ft_strncmp(env[min], env[next], ft_min(key_len, next_len));
			if ((ret > 0) || ((ret == 0) && (key_len > next_len)))
				min = next;
		}
		ft_swapstrs(&env[n++], &env[min]);
	}
	return (env);
}

/// @brief		Print variable export style
/// @param var	Pointer to a variable
static void	ft_print_export(char *var)
{
	char	*key;
	char	*value;
	int		key_len;

	if ((var[0] != '_') && (var[1] != '='))
	{
		if (!ft_strchr(var, '='))
			ft_fprintf(STDOUT_FILENO, "declare -x %s\n", var);
		else
		{
			key_len = (ft_strchr(var, '=') + 1 - var);
			key = ft_substr(var, 0, key_len);
			value = ft_substr(var, key_len, ft_strlen(var));
			ft_fprintf(STDOUT_FILENO, "declare -x %s\"%s\"\n", key, value);
			free(key);
			free(value);
		}
	}
}

/** @} */
