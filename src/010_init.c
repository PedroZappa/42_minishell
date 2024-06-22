/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   010_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:53:41 by passunca          #+#    #+#             */
/*   Updated: 2024/06/22 10:00:14 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup init Init
* @{
*
* @brief		Initialize minishell
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief		Initialize minishell
/// @param sh	Pointer to a t_shell struct
/// @param envp	Pointer to environment variables
/// @return		SUCCESS(0)
///				FAILURE(1)
/// @details	
///	- Allocate memory for minishell
///	- Initialize envp (primary env)
///	- Alloc envt (temporary env)
///	- Get HOME var
///	- Initialize heredoc
///	- Get snapshot of termios interface state
///	- Set readline() editing mode to VI
/// @note		Used in main()
int	ft_init(t_shell *sh, char **envp)
{
	sh->envp = ft_init_env(envp);
	sh->envt = ft_calloc(1, sizeof(char *));
	if (!sh->envp || !sh->envt)
		return (ft_err(ENV_INIT_ERR, errno), FAILURE);
	sh->home = ft_get_var("HOME", sh->envp, NULL);
	sh->heredoc = ft_strdup("");
	ft_get_termios(STDIN_FILENO, &sh->termios);
	rl_editing_mode = VI;
	return (SUCCESS);
}

/** @} */
