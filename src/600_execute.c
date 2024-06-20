/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:10:50 by passunca          #+#    #+#             */
/*   Updated: 2024/06/20 16:26:34 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief			Execute commands
/// @param sh		Pointer to a t_shell struct
/// @return			0 on success, 1 on failure.
/// @details		- Get path and split it
///					- Execute commands
///					- Flush stdin
int	ft_execute(t_shell *sh)
{
	sh->path = ft_split_path(sh->envp);
	ft_set_termios(STDIN_FILENO, TCSAFLUSH, &sh->termios);
	return (SUCCESS);
}
