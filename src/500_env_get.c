/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   500_env_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:02:06 by passunca          #+#    #+#             */
/*   Updated: 2024/07/15 20:20:39 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup env_get Set environment variable
* @{
*
* @brief		Get Environment variable
* @version		1.0
***/

#include "../inc/minishell.h"

static char	*ft_extract_var(char *select, char **env);

/// @brief			Initialize env
/// @param env		Pointer to environment variables array
/// @return			SUCCESS(Pointer to new env array)
///					FAILURE(NULL)
/// @note			Used in ft_init()
char	**ft_init_env(char **env)
{
	char	**new_env;
	int		n;

	n = 0;
	while (env[n])
		++n;
	new_env = ft_calloc((n + 1), sizeof(char *));
	if (!new_env)
		return (ft_err(MALLOC_ERR, errno), NULL);
	n = -1;
	while (env[++n])
	{
		new_env[n] = ft_strdup(env[n]);
		if (!new_env[n])
			return (NULL);
	}
	new_env[n] = NULL;
	return (new_env);
}

/// @brief			Get a var from ENV
/// @param var		Var to get
/// @param envp		Pointer to array of pointers, primary env
/// @return			SUCCESS(var2get)
///					FAILURE(NULL)
/// @note			Used in ft_init()
char	*ft_get_var(char *var, char **envp)
{
	char	*var2get;

	var2get = ft_extract_var(var, envp);
	return (var2get);
}

/// @brief			Extract selected variable from env
/// @param select	Var to be extracted
/// @param env		Pointer to array of environment variables
/// @return			SUCCESS(requested var)
///					FAILURE(NULL)
/// @note			Used in ft_get_var()
static char	*ft_extract_var(char *select, char **env)
{
	char	*tmp;
	char	*var;
	int		len;

	if ((select == NULL) || (env == NULL))
		return (NULL);
	tmp = ft_strjoin(select, "=");
	len = ft_strlen(tmp);
	var = NULL;
	while (*env)
	{
		if (ft_strncmp(tmp, *env, len) == 0)
		{
			var = ft_strdup(*env + len);
			break ;
		}
		++env;
	}
	free(tmp);
	return (var);
}

/// @brief			Find variable index in env
/// @param var		Pointer to variable string
/// @param env		Pointer to array of environment variables
/// @return			SUCCESS(var index in env)
///					FAILURE(-1)
///	@note			Used in ft_get_var() ...
int	ft_get_var_index(char *var, char **env)
{
	int	key_len;
	int	i;

	if (!env)
		return (NO_ENV);
	key_len = ft_strlen(var);
	i = -1;
	while (env[++i])
	{
		if ((ft_strncmp(var, env[i], key_len) == SUCCESS)
			&& ((env[i][key_len] == '=') || (env[i][key_len] == '\0')))
			return (i);
	}
	return (NO_VAR);
}

/** @} */
