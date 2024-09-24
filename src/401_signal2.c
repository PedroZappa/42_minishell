/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   401_signal2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:52:04 by gfragoso          #+#    #+#             */
/*   Updated: 2024/09/17 15:59:11 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief			Heredoc fork signal handler
/// @param signo	Signal number (or -1 to set sh and vars)
///	@note			Used in ft_sgnal_handler()
void	ft_heredoc_sighandler(int signo, t_shell *sh, t_hd_vars *vars)
{
	static t_shell		*hd_sh = NULL;
	static t_hd_vars	*hd_vars = NULL;

	if (signo == -1)
	{
		hd_sh = sh;
		hd_vars = vars;
		return ;
	}
	ft_free_heredoc(hd_sh);
	ft_free_sh_partial(hd_sh);
	if (hd_vars != NULL)
	{
		ft_free(hd_vars->delim);
		ft_free(hd_vars->ret);
		ft_free_tks(&hd_vars->tk);
		ft_lstclear(&hd_vars->list, free);
	}
	rl_on_new_line();
	write(1, "\n", 1);
	exit(130);
}

/// @brief			Heredoc signal setter
/// @details		Handles SIGINT and SIGTERM
/// @note			Used in ft_exec_fork()
void	ft_heredoc_sigset(void)
{
	signal(SIGINT, (void *)ft_heredoc_sighandler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, (void *)ft_heredoc_sighandler);
}

/// @brief			Set signals to be ignored
/// @details		On SIGINT, SIGQUIT and SIGTERM
void	ft_sigignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
