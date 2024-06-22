/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_termios.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:10:25 by passunca          #+#    #+#             */
/*   Updated: 2024/06/20 18:20:19 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup termios Termios
* @{
*
* @brief		Termios Interface
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			Get Termios Interface State of a given fd
/// @param fd
/// @param termios	Pointer to Termios Interface structure
/// @var term_conn	Gets tcsgetattribute() return for error handling
/// @details		- Get Termios Attribute
///					- Handle Failure
/// @note			Used in ft_init()
void	ft_get_termios(int fd, t_term *termios)
{
	int		term_conn;

	term_conn = tcgetattr(fd, termios);
	if (term_conn != SUCCESS)
		ft_err(TERMIOS_ERR, errno);
}

/// @brief			Set Termios Interface
/// @param fd
/// @param termios	Pointer to Termios Interface structure
/// @var term_conn	Gets tcsetattribute() return for error handling
/// @details		- Get Termios Attribute
///					- Handle Failure
/// @note			Used in ft_execute()
void	ft_set_termios(int fd, int opts, t_term *termios)
{
	int		term_conn;

	term_conn = tcsetattr(fd, opts, termios);
	if (term_conn != SUCCESS)
		ft_err(TERMIOS_ERR, errno);
}

/** @} */
