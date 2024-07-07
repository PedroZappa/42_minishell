/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   740_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:25:33 by passunca          #+#    #+#             */
/*   Updated: 2024/07/07 11:34:49 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_clear(int n)
{
	(void)n;
    ft_printf("\033[H\033[J");
	return (SUCCESS);
}

