/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   900_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:35:23 by passunca          #+#    #+#             */
/*   Updated: 2024/06/14 17:45:32 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @file			900_errirs.c
* @brief		Error functions
* @version		1.0
* @author		passunca
***/

#include "../inc/minishell.h"

int	ft_err(char *msg, int status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	g_exit = status;
	return (FAILURE);
}
