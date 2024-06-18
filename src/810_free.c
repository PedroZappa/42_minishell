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

static int	ft_free_arr(char **array, int err);

/// @brief		Handles freeing memory
void	ft_free(t_shell **sh)
{
	if (sh)
	{
		ft_free_arr(sh->envp, 0);
		free(sh);
	}
}

static int	ft_free_arr(char **array, int err)
{
	int	i;

	if (!array)
		return (err);
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	return (err);
}
