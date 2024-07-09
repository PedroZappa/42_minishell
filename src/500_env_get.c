/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   500_env_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:02:06 by passunca          #+#    #+#             */
/*   Updated: 2024/07/09 21:14:35 by passunca         ###   ########.fr       */
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
/// @details		- Count variables
///					- Allocate memory
///					- Copy variables
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
/// @param envt		Pointer to array of pointers, temporary env
/// @return			SUCCESS(var2get)
///					FAILURE(NULL)
/// @details		- Extract from envp
///					- If NULL extract from temporary env;
/// @note			Used in ft_init()
char	*ft_get_var(char *var, char **envp, char**envt)
{
	char	*var2get;

	var2get = ft_extract_var(var, envp);
	if (var2get == NULL)
		var2get = ft_extract_var(var, envt);
	return (var2get);
}

/// @brief			Extract selected variable from env
/// @param select	Var to be extracted
/// @param env		Pointer to array of environment variables
/// @return			SUCCESS(requested var)
///					FAILURE(NULL)
/// @detail			- Check input for NULL
///					- Format select string
///					- Take its length
///					- If selectec var is found set it to var and break
/// @note			Used in ft_get_var()
static char	*ft_extract_var(char *select, char **envp)
{
	char	*tmp;
	char	*var;
	int		len;

	if ((select == NULL) || (envp == NULL))
		return (NULL);
	tmp = ft_strjoin(select, "=");
	len = ft_strlen(tmp);
	var = NULL;
	while (*envp)
	{
		if (!ft_strncmp(tmp, *envp, len))
		{
			var = ft_strdup(*envp + len);
			break ;
		}
		++envp;
	}
	free(tmp);
	return (var);
}

/// @brief			Find variable index in env
/// @details		- Check if env is NULL
/// 				- Get length of variable to search for
///					- Loop through environment variables
///						- If variable is found and it ends with = or \0,
///						return its index,
/// @param var		Pointer to variable string
/// @param env		Pointer to array of environment variables
/// @return			SUCCESS(var index in env)
///					FAILURE(-1)
///	@note			Used in ft_get_var() ...
int	ft_get_var_index(char *var, char **env)
{
	int key_len;
	int i;

	if (!env)
		return (NO_ENV);
	key_len = ft_strlen(var);
	i = -1;
	while (env[++i])
	{
		if ((ft_strncmp(var, env[i], key_len) \
			&& (((env[i][key_len] == '=') \
			|| (env[i][key_len] == '\0')))))
			return (i);
	}
	return (NO_VAR);
}

/** @} */
