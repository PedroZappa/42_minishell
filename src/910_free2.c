/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   901_free2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:43:52 by gfragoso          #+#    #+#             */
/*   Updated: 2024/08/29 22:43:52 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief		Handles freeing a pointer
/// @param ptr	Pointer to be freed
void	ft_free_any(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	ptr = NULL;
}
