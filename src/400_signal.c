/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   400_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:46:27 by passunca          #+#    #+#             */
/*   Updated: 2024/06/22 10:05:25 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup signal Signal
* @{
*
* @brief		Signal handling
* @version		1.0
***/

#include "../inc/minishell.h"

static void	ft_signal_handler(int signo);

/// @brief			Set signal handlers
/// @details		On SIGINT and SIGQUIT
/// @note			Used in ft_sh_loop()
void		ft_sigset(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

/// @brief			Signal handler
/// @param signo	Signal number
/// @details		On SIGINT
///	- Replace contents of rl_line_buffer with empty string
///	- Write newline
///	- Announce new line
///	- Redisplay line with cleared rl_line_buffer
///	- Set g_exit to EXIT_SIGINT
///	@note			Used in ft_sgnal_handler()
static void	ft_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit = EXIT_SIGINT;
	}
}

/** @} */
