/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   300_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:48:25 by passunca          #+#    #+#             */
/*   Updated: 2024/06/19 18:24:53 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief			Parser
/// @param sh		Pointer to a t_shell struct
/// @param line_buf	Line buffer
/// @var tks		Pointer to a t_token struct
/// @return			Return 0 on success, 1 on failure
/// @details		- Call readline to display prompt
///					- Add line to history
///					- Call tokenizer
///					- Handle case where tk expands to a blank
///					- Validate syntax
///					- Count commands
///					- Alloc cmds array
///					- Count cmd's arguments
///					- Initialize cmd's list
///					- Parse cmds
///					- Free tks
///	@note			Used in ft_sh_loop()
int	ft_parser(t_shell *sh, char **line_buf)
{
	t_token	*tks;

	tks = NULL;
	*line_buf = readline(GRN"minishell > "NC);
	if (!*line_buf)
		*line_buf = ft_strdup("exit");
	add_history(*line_buf);
	if (ft_tokenizer(sh, line_buf, &tks) == FAILURE)
		return (ft_free_tks(&tks));
	return (SUCCESS);
}
