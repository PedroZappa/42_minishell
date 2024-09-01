/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_termios.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:10:25 by passunca          #+#    #+#             */
/*   Updated: 2024/08/17 09:43:35 by passunca         ###   ########.fr       */
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
/// @note			Used in ft_init()
void	ft_get_termios(int fd, t_term *termios)
{
	int		term_conn;

	term_conn = tcgetattr(fd, termios);
	if (term_conn != SUCCESS)
		ft_return_err(TERMIOS_ERR, term_conn, FAILURE);
}

/// @brief			Set Termios Interface
/// @param fd		File descriptor
/// @param opts		Termios Interface options
/// @param termios	Pointer to Termios Interface structure
/// @note			Used in ft_execute()
void	ft_set_termios(int fd, int opts, t_term *termios)
{
	int		term_conn;

	term_conn = tcsetattr(fd, opts, termios);
	if (term_conn != SUCCESS)
		ft_return_err(TERMIOS_ERR, term_conn, FAILURE);
}

/** @} */
