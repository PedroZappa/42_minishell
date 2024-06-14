/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_termios.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:10:25 by passunca          #+#    #+#             */
/*   Updated: 2024/06/14 17:11:58 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @file			200_termios.c
* @brief		Termios Interface
* @version		1.0
* @author		passunca
***/

#include "../inc/minishell.h"

/// @brief		Get Termios Interface
/// @param		Pointer to Termios Interface structure
/// @details	- Get Termios Attribute
/// - Handle Failure
void	ft_get_termios(int fd, struct termios *termios)
{
	int		term_conn;

	term_conn = tcgetattr(fd, termios);
	if (term_conn != SUCCESS)
		ft_err(TERMIOS_ERR);
}
