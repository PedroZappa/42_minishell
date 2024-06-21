/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   510_env_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 09:15:42 by passunca          #+#    #+#             */
/*   Updated: 2024/06/21 10:54:15 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**ft_env_add_var(char **env, char *new_var);

/// @brief			Set environment variable
/// @param var		Pointer to variable to be set
/// @param val		Pointer to value to be set
/// @param env		Pointer to array of environment variables
/// @var new		Pointer for local string manipulation
/// @var i			Environment variables iterator
/// @return			SUCCESS(0) or FAILURE(-1)
/// @details		Build new variable string
///					- If val exists	concatenate "=" and val to var;
///					- else just copy var;
///					- Get var's index in env
///					- If var is not found in env, add it
///					- Else, if it exists and has a new value, update it
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
		if (ft_strncmp(new, (*env)[i], ft_max(ft_strlen(new), \
			ft_strlen((*env)[i]))) != SUCCESS)
			ft_swapstrs(&(*env)[i], &new);
		free(new);
	}
	return (SUCCESS);
}

/// @brief			Extract variable index from env
/// @param var		Pointer to variable string
/// @param env		Pointer to array of environment variables
/// @var i			Environment variables iterator
/// @var len		To store variable length
/// @return			SUCCESS(var index in env) or FAILURE(-1)
/// @details		- Check if env is NULL
/// 				- Get variable to search for length
///					- Loop through environment variables
///						- If variable is found and it ends with = or \0,
///						return its index,
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
/// @var new_env	Pointer to new array of environment variables
/// @var i			Environment variables iterator
/// @return			SUCCESS(Pointer to new env array) or FAILURE(NULL)
/// @details		- Loop through old environment variables
///					- Count variables in old env
///					- Increment var count by 2 to account for new var & NULL
///					- Allocate new array
///					- Copy old env to new array
///					- Add new var
///					- NULL terminal new array
///					- Free old env
///	@note			Used in ft_set_var() ...
static char	**ft_env_add_var(char **env, char *new_var)
{
	char	**new_env;
	int		i;

	if (!env)
		return (ft_err(ENV_NULL_ERR, errno), NULL);
	i = 0;
	while (env[i])
		++i;
	i += 2;
	new_env = ft_calloc(i, sizeof(char *));
	if (!new_env)
		return (ft_err(MALLOC_ERR, errno), NULL);
	i = -1;
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = new_var;
	new_env[++i] = NULL;
	ft_free_arr(env);
	return (new_env);
}
