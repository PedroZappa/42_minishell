/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   510_env_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 09:15:42 by passunca          #+#    #+#             */
/*   Updated: 2024/07/11 16:55:32 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup env_set Set environment variable
* @{
*
* @brief		Set environment variable
* @version		1.0
* @author		passunca
***/

#include "../inc/minishell.h"

static char	**ft_env_add_var(char **env, char *new_var);

/// @brief			Set environment variable
/// @param var		Pointer to variable to be set
/// @param val		Pointer to value to be set
/// @param env		Pointer to array of environment variables
/// @return			SUCCESS(0)
///					FAILURE(-1)
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
	int		max;
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
		max = ft_max(ft_strlen(new), ft_strlen((*env)[i]));
		if (ft_strncmp(new, (*env)[i], max) != SUCCESS)
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
/// @return			SUCCESS(Pointer to new env array)
///					FAILURE(NULL)
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

/// @brief			Delete variable from env and return new env
/// @details		
/// - Loop through old environment variables and count them
/// - Allocate space
/// - Copy old env to new array
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
	if (!new_env)
		return (ft_err(MALLOC_ERR, errno), NULL);
	j = 0;
	i = -1;
	while (env[++i])
	{
		var = ft_substr(env[i], 0,
				(ft_strlen(env[i] - ft_strlen(ft_strchr(env[i], '=')))));
		if (ft_strncmp(var, to_del, ft_max(ft_strlen(var), ft_strlen(to_del))))
			new_env[j++] = ft_strdup(env[i]);
		free(var);
	}
	new_env[j] = NULL;
	ft_free_arr(env);
	return (new_env);
}

void	ft_build_last_cmd(t_shell *sh, int n)
{
	char	*exec_path;
	int		i;

	if (sh->cmds[n].argv[0])
	{
		i = -1;
		while (sh->path[++i])
		{
			exec_path = ft_strjoin(sh->path[i], sh->cmds[n].argv[0]);
			if (exec_path)
			{
				if (access(exec_path, X_OK) == 0)
				{
					ft_set_var("_", exec_path, &sh->envp);
					ft_free(sh->cmds[n].argv[0]);
					sh->cmds[n].argv[0] = exec_path;
					break ;
				}
				ft_free(exec_path);
			}
		}
	}
	else
		ft_set_var("_", sh->cmds[n].argv[0], &sh->envp);
}

/** @} */
