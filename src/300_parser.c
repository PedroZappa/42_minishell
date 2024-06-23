/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   300_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:48:25 by passunca          #+#    #+#             */
/*   Updated: 2024/06/23 11:20:47 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup parser Parser
* @{
*
* @brief		Parser
* @version		1.0
***/

#include "../inc/minishell.h"

static int	ft_check_syntax(t_token *tks);
static int	ft_count_cmds(t_token *tks);

/// @brief			Parser
/// @details
/// - Call readline to display prompt
///	- Add line to history
///	- Call tokenizer
///	- Handle case where tk expands to a blank
///	- Validate syntax
///	- Count commands
///	- Alloc cmds array
///	- Count cmd's arguments
///	- Initialize cmd's list
///	- Parse cmds
///	- Free tks
/// @param sh		Pointer to a t_shell struct
/// @param line_buf	Line buffer
/// @var tks		Pointer to a t_token struct
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
///	@note			Used in ft_sh_loop()
int	ft_parser(t_shell *sh, char **line_buf)
{
	t_token	*tks;

	tks = NULL;
	*line_buf = readline(GRN"minishell > "NC);
	if (!*line_buf)
		*line_buf = ft_strdup("exit");
	add_history(*line_buf);
	if (ft_tokenizer(sh, line_buf, &tks))
		return (ft_free_tks(&tks), FAILURE);
	return (ft_free_tks(&tks), SUCCESS);
	if (ft_check_syntax(tks))
		return (ft_free_tks(&tks), FAILURE);
	sh->n_cmds = ft_count_cmds(tks);
	sh->cmds = (t_cmd *)ft_calloc(sh->n_cmds, sizeof(t_cmd));
	if (!sh->cmds)
		return (ft_err(MALLOC_ERR, errno), FAILURE);
}

/// @brief Check if a given token's list is a valid command syntactically
/// @details
/// - If first token is a pipe, return failure
/// - Loop through token list
///		- If there is no next token, and the current tkn is a TK_PIPE or TK_OR
///		...
/// @param tks	Pointer to a t_token struct
/// @return		SUCCESS(0)
/// @note		Used in ft_parser()
static int	ft_check_syntax(t_token *tks)
{
	if (tks && (tks->type == TK_PIPE || tks->type == TK_OR))
		return (ft_syntax_err(tks->val, FAILURE));
	while(tks)
	{
		tks = tks->next;
	}
	return (SUCCESS);
}

static int	ft_count_cmds(t_token *tks)
{
	int	count;

	count = 0;
	while (tks)
	{
		if (!count)
			count = 1;
		if ((tks->type == TK_PIPE) || (tks->type == TK_OR))
			++count;
		tks = tks->next;
	}
	return (count);
}

/** @} */
