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

void	ft_free(t_shell *sh)
{
	if (sh->envp)
	{
		while (sh->envp)
		{
			free(*sh->envp);
			++(sh->envp);
		}
	}
	if (sh->envp)
		free(sh->envp);
	if (sh->envt)
		free(sh->envt);
	if (sh)
		free(sh);
}
