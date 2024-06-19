/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   300_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:48:25 by passunca          #+#    #+#             */
/*   Updated: 2024/06/19 15:48:28 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_parser(t_shell *sh, char **line_buf)
{
	t_token	*tks;

	(void)sh;
	(void)tks;
	tks = NULL;
	*line_buf = readline(GRN"minishell > "NC);
	if (!*line_buf)
		*line_buf = ft_strdup("exit");
	add_history(*line_buf);
	if (ft_tokenizer(sh, line_buf, &tks) == FAILURE)
		return (ft_free_tks(&tks));
	return (0);
}
