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

void	ft_heredoc_sighandler(int signal, t_shell *sh, t_hd_vars *vars)
{
	static t_shell		*hd_sh = NULL;
	static t_hd_vars	*hd_vars = NULL;

	if (signal == -1)
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
	exit(130);
}

/// @brief			Fork signal setter
/// @details		Handles SIGINT and SIGQUIT
/// @note			Used in ft_exec_fork()
void	ft_heredoc_sigset(void)
{
	signal(SIGINT, (void *)ft_heredoc_sighandler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, (void *)ft_heredoc_sighandler);
}

void	ft_sigignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
