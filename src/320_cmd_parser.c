/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   320_cmd_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:04:02 by gfragoso          #+#    #+#             */
/*   Updated: 2024/09/06 22:08:13 by gfragoso         ###   ########.fr       */
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

static t_token	*ft_parse_cmds_in(t_token *tks, t_cmd *cmd,
					t_ctrs *c);
static t_token	*ft_parse_cmds_inner(t_token *tks, t_cmd *cmd,
					t_ctrs *c);

/// @brief			Parse commands from token list
/// @param tks		Pointer to a t_token struct list
/// @param cmds		Pointer to an array of t_cmd structs
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_parse_cmds(t_token *tks, t_cmd *cmds)
{
	t_ctrs	c;

	c = (t_ctrs){0, 0, 0, 0};
	while (tks)
	{
		if (ft_cmd_allocate(cmds + c.i))
			return (FAILURE);
		c.j = 0;
		while (tks && tks->type != TK_PIPE && tks->type != TK_OR
			&& tks->type != TK_AND && tks->type != TK_PARENTESHIS)
			tks = ft_parse_cmds_inner(tks, cmds + c.i, &c);
		cmds[c.i].argv[c.j] = NULL;
		cmds[c.i].in_fd = -1;
		cmds[c.i].out_fd = -1;
		++c.i;
		if (tks)
			tks = tks->next;
	}
	return (SUCCESS);
}

/// @brief			Parse commands from token list
/// @param tks		Pointer to a t_token struct list
/// @param cmd		Pointer to a t_cmd struct
/// @param c		Pointer to a t_ctrs struct
t_token	*ft_parse_cmds_inner(t_token *tks, t_cmd *cmd, t_ctrs *c)
{
	if (tks->type == TK_CMD)
	{
		if (cmd->cmd == NULL)
			cmd->cmd = ft_strdup(tks->name);
		cmd->argv[c->j] = ft_strdup(tks->name);
		c->j += 1;
	}
	if (tks->type == TK_OUT)
	{
		if (tks->next == NULL)
			return (tks);
		cmd->out[c->k] = (t_redir)
		{ft_strdup(tks->next->name), RD_OUT};
		if (ft_strncmp(tks->name, ">>", INT_MAX) == 0)
			cmd->out[c->k].type = RD_OUT_APP;
		c->k++;
		tks = tks->next;
	}
	tks = ft_parse_cmds_in(tks, cmd, c);
	if (tks)
		tks = tks->next;
	return (tks);
}

/// @brief			Parse commands from token list
/// @param tks		Pointer to a t_token struct list
/// @param cmd		Pointer to a t_cmd struct
/// @param c		Pointer to a t_ctrs struct (counters)
t_token	*ft_parse_cmds_in(t_token *tks, t_cmd *cmd, t_ctrs *c)
{
	if (tks->type == TK_IN)
	{
		if (tks->next == NULL)
			return (tks);
		cmd->in[c->l++] = (t_redir)
		{ft_strdup(tks->next->name), RD_IN};
		tks = tks->next;
	}
	if (tks->type == TK_HEREDOC)
	{
		if (tks->next == NULL)
			return (tks);
		cmd->in[c->l++] = (t_redir)
		{ft_strdup(tks->next->name), RD_IN_HD};
		tks = tks->next;
	}
	return (tks);
}

/** @} */
