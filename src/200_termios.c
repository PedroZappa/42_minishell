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
* @date			2024/05/29
* @author		passunca
* @copyright	© 2024 passunca/gfragoso
***/

#include "../inc/minishell.h"

void	ft_init_termios(struct termios *termios)
{
	int		term_conn;

	term_conn = tcgetattr(STDIN_FILENO, termios);
	if (term_conn != SUCCESS)
		ft_err(TERMIOS_ERR);
}
