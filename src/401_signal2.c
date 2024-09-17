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

/// @brief			Fork signal setter
/// @details		Handles SIGINT and SIGQUIT
/// @note			Used in ft_exec_fork()
void	ft_heredoc_sigset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
