/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   300_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:48:25 by passunca          #+#    #+#             */
/*   Updated: 2024/07/08 14:10:45 by passunca         ###   ########.fr       */
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
static int	ft_check_syntax2(t_token *tk);
static int	ft_count_cmds(t_token *tks);

/// @brief			Parser
/// @param sh		Pointer to a t_shell struct
/// @param line_buf	Line buffer
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
///	@note			Used in ft_sh_loop()
int	ft_parser(t_shell *sh, char *line_buf)
{
	t_token	*tks;

	tks = NULL;
	if (ft_readline(&line_buf, sh))
		return (ft_free(line_buf), FAILURE);
	if (ft_tokenizer(sh, line_buf, &tks))
		return (ft_free_tks(&tks), FAILURE);
	ft_free(line_buf);
	if (ft_check_syntax(tks))
		return (ft_free_tks(&tks), FAILURE);
	sh->n_cmds = ft_count_cmds(tks);
	sh->cmds = (t_cmd *)ft_calloc(sh->n_cmds, sizeof(t_cmd));
	if (sh->cmds == NULL)
		return (ft_err(MALLOC_ERR, errno), FAILURE);
	if (sh->n_cmds == NO_CMDS)
		return (ft_free_nocmds(sh->cmds, sh->n_cmds, &tks));
	ft_count_args(sh, tks);
	if (ft_parse_cmds(tks, sh->cmds))
		return (ft_free_tks(&tks), FAILURE);
	return (ft_free_tks(&tks), SUCCESS);
}

/// @brief 			Check if a given token's list is 
///						a valid command syntactically
/// @param tk		Pointer to a t_token struct
/// @return			SUCCESS(0)
/// @note			Used in ft_parser()
static int	ft_check_syntax(t_token *tk)
{
	int	exit;

	exit = 0;
	if (tk && (tk->type == TK_PIPE || tk->type == TK_OR || tk->type == TK_AND))
		return (ft_syntax_err(tk->name));
	while (tk)
	{
		if (tk->next == NULL && (tk->type == TK_PIPE || tk->type == TK_OR
				|| tk->type == TK_AND
				|| tk->type == TK_HEREDOC))
			return (ft_syntax_err(tk->name));
		exit = ft_check_syntax2(tk);
		if (exit)
			return (exit);
		tk = tk->next;
	}
	return (SUCCESS);
}

/// @brief 			Second section of ft_check_syntax
/// @param tk		Pointer to a t_token struct
/// @return			SUCCESS(0)
/// @note			Used in ft_parser()
static int	ft_check_syntax2(t_token *tk)
{
	if (tk->next && ((tk->type == TK_PIPE) && (tk->next->type == TK_PIPE))
		&& ((tk->type == TK_PIPE) || (tk->next->type == TK_OR))
		&& ((tk->type == TK_OR))
		&& ((tk->type == TK_OR) || (tk->next->type == TK_OR)))
		return (ft_syntax_err(tk->name));
	if (tk->next && ((tk->type == TK_IN || tk->type == TK_OUT
				|| tk->type == TK_HEREDOC) && (tk->next->type != TK_CMD)))
		return (ft_syntax_err(tk->next->name));
	if ((tk->next == NULL) && ((tk->type == TK_IN || tk->type == TK_OUT)))
		return (ft_syntax_err("newline"));
	return (SUCCESS);
}

/// @brief			Count commands
/// @param tks		Pointer to a t_token struct
/// @return			Number of commands
static int	ft_count_cmds(t_token *tks)
{
	int	count;

	count = 0;
	while (tks)
	{
		if (count == 0)
			count = 1;
		if ((tks->type == TK_AND) || (tks->type == TK_OR)
			|| (tks->type == TK_PIPE))
			++count;
		tks = tks->next;
	}
	return (count);
}

/** @} */
