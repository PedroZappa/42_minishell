/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   510_env_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 09:15:42 by passunca          #+#    #+#             */
/*   Updated: 2024/06/21 09:58:47 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	ft_var_from_env(char *var, char **env)
{
	(void)var;
	(void)env;
	return (SUCCESS);
}

char	**ft_env_add_var(char **env, char *new_var)
{
	(void)env;
	(void)new_var;
	return (NULL);
}
