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

/// @brief			Get Termios Interface
/// @param fd
/// @param termios	Pointer to Termios Interface structure
/// @var term_conn	Gets tcsgetattribute() return for error handling
/// @details		- Get Termios Attribute
///					- Handle Failure
void	ft_get_termios(int fd, t_term *termios)
{
	int		term_conn;

	term_conn = tcgetattr(fd, termios);
	if (term_conn != SUCCESS)
		ft_err(TERMIOS_ERR);
}

/// @brief			Set Termios Interface
/// @param fd
/// @param termios	Pointer to Termios Interface structure
/// @var term_conn	Gets tcsetattribute() return for error handling
/// @details		- Get Termios Attribute
///					- Handle Failure
void	ft_set_termios(int fd, int opts, t_term *termios)
{
	int		term_conn;

	term_conn = tcsetattr(fd, opts, termios);
	if (term_conn != SUCCESS)
		ft_err(TERMIOS_ERR);
}

