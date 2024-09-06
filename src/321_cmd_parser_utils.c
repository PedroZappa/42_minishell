/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   321_cmd_parser_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:04:53 by gfragoso          #+#    #+#             */
/*   Updated: 2024/09/06 22:32:28 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief			Count a given command's arguments
/// @param sh		Pointer to a t_shell struct
/// @param tks		Pointer to a t_token struct
/// @note			Used in ft_parser()
void	ft_count_args(t_shell *sh, t_token *tks)
{
	t_token	*prev;
	int		i;

	i = 0;
	while (i < sh->n_cmds)
	{
		sh->cmds[i].argc = 0;
		prev = tks;
		while (tks && (tks->type != TK_PIPE))
		{
			if ((tks->type == TK_CMD) && (prev->type != TK_IN)
				&& (prev->type != TK_OUT) && (prev->type != TK_HEREDOC))
				++sh->cmds[i].argc;
			if ((prev->type == TK_IN) || (prev->type == TK_HEREDOC))
				++sh->cmds[i].n_in;
			if (prev->type == TK_OUT)
				++sh->cmds[i].n_out;
			prev = tks;
			tks = tks->next;
		}
		if (tks)
			tks = tks->next;
		++i;
	}
}

int	ft_cmd_allocate(t_cmd *cmd)
{
	cmd->argv = (char **)ft_calloc((cmd->argc + 1), sizeof(char *));
	if (cmd->argv == NULL)
		return (ft_err(MALLOC_ERR, errno), FAILURE);
	cmd->in = (t_redir *)ft_calloc((cmd->n_in + 1), sizeof(t_redir));
	if (cmd->in == NULL)
		return (ft_vfree(cmd->argv), ft_err(MALLOC_ERR, errno), FAILURE);
	cmd->out = (t_redir *)ft_calloc((cmd->n_out + 1), sizeof(t_redir));
	if (cmd->out == NULL)
		return (ft_vfree(cmd->argv), ft_vfree(cmd->in),
			ft_err(MALLOC_ERR, errno), FAILURE);
	return (0);
}
