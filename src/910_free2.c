/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   910_free2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:49:32 by gfragoso          #+#    #+#             */
/*   Updated: 2024/09/05 21:49:32 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup free Free functions
* @{
*
* @brief		Free functions
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief		Handles freeing memory
/// @param sh	Array to be freed
void	ft_vfree(void *ptr)
{
	if (ptr == NULL)
		return ;
	free(ptr);
}

void	ft_free_redir(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->in)
	{
		while (i < cmd->n_in)
			ft_free(cmd->in[i++].name);
		ft_vfree(cmd->in);
		cmd->in = NULL;
		if (cmd->in_fd != -1)
			close(cmd->in_fd);
	}
	i = 0;
	if (cmd->out)
	{
		while (i < cmd->n_out)
			ft_free(cmd->out[i++].name);
		ft_vfree(cmd->out);
		cmd->out = NULL;
		if (cmd->out_fd != -1)
			close(cmd->out_fd);
	}
}
/** @} */
