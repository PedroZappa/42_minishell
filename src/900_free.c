/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   810_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:12:55 by passunca          #+#    #+#             */
/*   Updated: 2024/06/17 15:19:15 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_free_arr(char **arr, int status);

/// @brief		Handles freeing memory
/// @param arr		Array to be freed
/// @param status	Exit status
int	ft_free_sh(t_shell *sh, int status)
{
	if (sh)
	{
		ft_free_arr(sh->path, status);
		ft_free_arr(sh->envp, status);
		ft_free_arr(sh->envt, status);
	}
	return (status);
}

/// @brief			Free array
/// @param arr		Array to be freed
/// @param status	Exit status
/// @var i			To iterate array members
/// @return			Returns status
static int	ft_free_arr(char **arr, int status)
{
	int	i;

	if (!arr)
		return (FAILURE);
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (status);
}
