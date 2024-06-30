/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   310_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:46:35 by passunca          #+#    #+#             */
/*   Updated: 2024/06/30 11:54:51 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief			Readline wrapper
/// @param line_buf	Line buffer
/// @note			Used in ft_parser()
void		ft_readline(char ***line_buf)
{
	**line_buf = readline(MAG"$>"NC);
	if (!**line_buf)
		**line_buf = ft_strdup("exit");
	add_history(**line_buf);
}
