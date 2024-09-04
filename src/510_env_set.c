/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   510_env_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 09:15:42 by passunca          #+#    #+#             */
/*   Updated: 2024/08/08 12:33:06 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @defgroup env_set Set environment variable
* @{
*
* @brief		Set environment variable
* @version		1.0
***/

#include "../inc/minishell.h"

static char	**ft_env_add_var(char **env, char *new_var);

/// @brief			Set environment variable
/// @param var		Pointer to variable to be set
/// @param val		Pointer to value to be set
/// @param env		Pointer to array of environment variables
/// @return			SUCCESS(0)
///					FAILURE(-1)
///	@note			Used in ...
int	ft_set_var(char *var, char *val, char ***env)
{
	char	*new;
	int		i;

	if (!*env)
		return (NO_ENV);
	if (val)
		new = ft_strjoin_free(ft_strjoin(var, "="), ft_strdup(val));
	else
		new = ft_strdup(var);
	i = ft_var_from_env(var, *env);
	if (i == NO_VAR)
		(*env) = ft_env_add_var(*env, new);
	else
	{
		ft_swapstrs(&(*env)[i], &new);
		free(new);
	}
	return (SUCCESS);
}

/// @brief			Extract variable index from env
/// @param var		Pointer to variable string
/// @param env		Pointer to array of environment variables
/// @return			SUCCESS(var index in env)
///					FAILURE(-1)
///	@note			Used in ft_set_var() ...
int	ft_var_from_env(char *var, char **env)
{
	int	i;
	int	len;

	if (!*env)
		return (NO_ENV);
	i = -1;
	len = ft_strlen(var);
	while (env[++i])
	{
		if ((ft_strncmp(var, env[i], len) == SUCCESS) \
			&& ((env[i][len] == '=') || (env[i][len] == '\0')))
			return (i);
	}
	return (NO_VAR);
}

/// @brief			Add new variable to env
/// @param env		Pointer to array of environment variables
/// @param new_var	Pointer to new variable to add to env
/// @return			SUCCESS(Pointer to new env array)
///					FAILURE(NULL)
///	@note			Used in ft_set_var() ...
static char	**ft_env_add_var(char **env, char *new_var)
{
	char	**new_env;
	int		i;

	if (env == NULL)
		return (ft_err(ENV_NULL_ERR, errno), NULL);
	i = 0;
	while (env[i])
		++i;
	i += 2;
	new_env = ft_calloc(i, sizeof(char *));
	if (new_env == NULL)
		return (ft_err(MALLOC_ERR, errno), NULL);
	i = -1;
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = new_var;
	new_env[++i] = NULL;
	ft_free_arr(env);
	return (new_env);
}

/// @brief			Delete variable from env and return new env
/// @param env		Pointer to array of environment variables
/// @param to_del	Pointer to variable to delete
///	@return			SUCCESS(Pointer to new env array)
///	@return			FAILURE(NULL)
char	**ft_env_del_var(char **env, char *to_del)
{
	char	**new_env;
	char	*var;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		++i;
	new_env = ft_calloc(i, sizeof(char *));
	if (new_env == NULL)
		return (ft_err(MALLOC_ERR, errno), NULL);
	j = 0;
	i = -1;
	while (env[++i])
	{
		var = ft_substr(env[i], 0,
				(ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '='))));
		if (ft_strncmp(var, to_del, INT_MAX) != 0)
			new_env[j++] = ft_strdup(env[i]);
		free(var);
	}
	new_env[j] = NULL;
	ft_free_arr(env);
	return (new_env);
}

/** @} */
