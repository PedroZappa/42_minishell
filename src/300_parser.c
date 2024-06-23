/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   300_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:48:25 by passunca          #+#    #+#             */
/*   Updated: 2024/06/23 11:56:53 by passunca         ###   ########.fr       */
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
static void	ft_count_args(t_shell *sh, t_token *tks);
static int	ft_parse_cmds(t_token *tks, t_cmd *cmds, int i, int j);

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
	if (sh->n_cmds == NO_CMDS)
		return (ft_free_nocmds(sh->cmds, sh->n_cmds, &tks));
	ft_count_args(sh, tks);
	if (ft_parse_cmds(tks, sh->cmds, 0, 0))
		return (ft_free_tks(&tks), FAILURE);
	return (ft_free_tks(&tks), SUCCESS);
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

/// @brief			Count commands
/// @param tks		Pointer to a t_token struct
/// @var count		Count of commands
/// @return			Number of commands
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

/// @brief			Count a given command's arguments
/// @details
/// - For each parsed command:
///		- Initialize argument counter
///		- Save current token in prev
///		- Loop through token list to get the current command arguments
///			- If token is not an input or output redirection
///				- Increment argument counter
///			- Save current token in prev
///			- Move to next token
///		- Move to next token
///		- Increment command counter
/// @param sh		Pointer to a t_shell struct
/// @param tks		Pointer to a t_token struct
/// @var prev		Pointer to the previous token
/// @var i			Count of commands
/// @note			Used in ft_parser()
static void	ft_count_args(t_shell *sh, t_token *tks)
{
	t_token	*prev;
	int		i;

	while (i < sh->n_cmds)
	{
		sh->cmds[i].argc = 0;
		prev = tks;
		while (tks && (tks->type != TK_PIPE))
		{
			if ((tks->type == TK_CMD) \
				&& (prev->type != TK_IN) && (prev->type != TK_OUT))
				++sh->cmds[i].argc;
			prev = tks;
			tks = tks->next;
		}
		if (tks)
			tks = tks->next;
		++i;
	}
}

/// @brief			Parse commands from token list
/// @param tks		Pointer to a t_token struct list
/// @param cmds		Pointer to an array of t_cmd structs
/// @param i		Count of commands
/// @param j		Count of arguments
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
static int	ft_parse_cmds(t_token *tks, t_cmd *cmds, int i, int j)
{
	while (tks)
	{
		cmds[i].argv = ft_calloc((cmds[i].argc + 1), sizeof(char *));
		if (!cmds[i].argv)
			return (ft_err(MALLOC_ERR, errno), FAILURE);
		j = 0;
		while (tks && (tks->type != TK_PIPE) && (tks->type != TK_OR))
		{
			if (tks->type == TK_CMD)
				cmds[i].argv[j++] = ft_strdup(tks->val);
			if (tks)
				tks = tks->next;
		}
		if (tks)
			tks = tks->next;
		cmds[i].argv[j] = NULL;
		++i;
	}
	return (SUCCESS);
}

/** @} */
