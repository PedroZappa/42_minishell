/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   900_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:12:55 by passunca          #+#    #+#             */
/*   Updated: 2024/06/19 15:50:29 by passunca         ###   ########.fr       */
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
/// @return			Returns status
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

int	ft_free_tks(t_token **tk)
{
	(void)tk;
	return (0);
}
