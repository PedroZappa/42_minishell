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

/** @} */
