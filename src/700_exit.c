/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   700_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 21:22:16 by passunca          #+#    #+#             */
/*   Updated: 2024/07/16 14:56:54 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup exit Exit built-in
* @{
*
* @brief		Exit built-in
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			exit built-in
/// @param sh		Pointer to a t_shell struct
int	ft_exit(t_shell *sh)
{
	errno = EXIT_SUCCESS;
	ft_free_sh(sh);
	exit(EXIT_SUCCESS);
}

/** @} */
