/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   500_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:02:06 by passunca          #+#    #+#             */
/*   Updated: 2024/06/14 23:14:28 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_extract_var(char *select, char **env);

/// @brief			Get a var from ENV
/// @param var		Var to get
/// @param envp		Pointer to array of pointers, primary env
/// @param envt		Pointer to array of pointerdataemdata env
/// @var var2get	Variable to extract from env
/// @return			Selected variable to get
/// @details		- Extract from envp
///					- If NULL extract from temporary env;
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
/// @var tmp		Pointer to temporary variable
/// @var var		Pointer to return variable
/// @var len		Length of the selected variable
/// @return			Pointer to selected var string or NULL
/// @detail			- Check input for NULL
///					- Format select string
///					- Take its length
///					- If selectec var is found set it to var and break
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
			var = ft_strdup((*envp + len));
			break ;
		}
		++envp;
	}
	free(tmp);
	return (var);
}
