/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   400_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:46:27 by passunca          #+#    #+#             */
/*   Updated: 2024/07/08 12:39:27 by passunca         ###   ########.fr       */
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
void	ft_sigset(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

/// @brief			Signal handler
/// @param signo	Signal number
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

/// @brief			Fork signal setter
/// @details		Handles SIGINT and SIGQUIT
/// @note			Used in ft_exec_fork()
void	ft_fork_sigset(void)
{
	signal(SIGINT, ft_fork_sighandler);
	signal(SIGQUIT, ft_fork_sighandler);
}

/// @brief			Fork signal handler
/// @param sig		Signal number
/// @note			Used in ft_sigset() and ft_exec_fork()
void	ft_fork_sighandler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
		g_exit = EXIT_SIGQUIT;
	}
	else if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_exit = EXIT_SIGINT;
	}
}

/** @} */
