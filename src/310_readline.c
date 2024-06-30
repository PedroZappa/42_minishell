/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   310_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:46:35 by passunca          #+#    #+#             */
/*   Updated: 2024/06/30 11:51:33 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void		ft_readline(char ***line_buf)
{
	**line_buf = readline(MAG"$>"NC);
	if (!**line_buf)
		**line_buf = ft_strdup("exit");
	add_history(**line_buf);
}
