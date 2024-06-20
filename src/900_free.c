/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   900_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:12:55 by passunca          #+#    #+#             */
/*   Updated: 2024/06/20 18:35:38 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_free_arr(char **arr, int status);

/// @brief		Handles freeing memory
/// @param arr		Array to be freed
/// @param status	Exit status
int	ft_free_sh(t_shell *sh, int status)
{
	if (sh)
	{
		ft_free_arr(sh->envp, 0);
		ft_free_arr(sh->envt, 0);
		ft_free_arr(sh->path, 0);
		free(sh->heredoc);
		free(sh->home);
		free(sh);
	}
	return (status);
}

/// @brief			Free array
/// @param arr		Array to be freed
/// @param status	Exit status
/// @var i			To iterate array members
/// @return			SUCCESS(return status) or FAILURE(1)
int	ft_free_arr(char **arr, int status)
{
	int	i;

	if (!arr)
		return (FAILURE);
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		++i;
	}
	free(arr);
	return (status);
}

/// @brief			Free tokens
/// @param tk		Pointer to a list of t_token structs
/// @var tmp		Pointer to hold next token in the list
/// @return			SUCCESS(0) or FAILURE(1)
int	ft_free_tks(t_token **tk)
{
	t_token	*tmp;

	if (!tk)
		return (FAILURE);
	while (*tk)
	{
		tmp = (*tk)->next;
		free((*tk)->val);
		free(*tk);
		*tk = tmp;
	}
	return (SUCCESS);
}
