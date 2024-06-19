/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   300_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:48:25 by passunca          #+#    #+#             */
/*   Updated: 2024/06/19 12:48:49 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_parser(t_shell *sh, char **line_buf)
{
	t_token	*tk;

	(void)sh;
	(void)tk;
	tk = NULL;
	*line_buf = readline("minishell > ");
	if (!*line_buf)
		*line_buf = ft_strdup("exit");
	add_history(*line_buf);
	return (0);
}
