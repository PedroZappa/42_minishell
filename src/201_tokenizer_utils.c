/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   201_tokenizer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:45:42 by gfragoso          #+#    #+#             */
/*   Updated: 2024/09/02 22:16:33 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @defgroup 	tokenizer_utils Tokenizer utils
* @{
*
* @brief		Tokenizer utils
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			Initialize t_tk_ops array with all supported tokens
/// @param ops		Pointer to an array of t_tk_ops structs
void	ft_init_ops(t_tk_ops *ops)
{
	ops[0] = (t_tk_ops){"<<", TK_HEREDOC, 2};
	ops[1] = (t_tk_ops){"<", TK_IN, 1};
	ops[2] = (t_tk_ops){">>", TK_OUT, 2};
	ops[3] = (t_tk_ops){">", TK_OUT, 1};
	ops[4] = (t_tk_ops){"|", TK_PIPE, 1};
	ops[5] = (t_tk_ops){" ", TK_BLANK, 1};
	ops[6] = (t_tk_ops){"\n", TK_BLANK, 1};
	ops[7] = (t_tk_ops){"\v", TK_BLANK, 1};
	ops[8] = (t_tk_ops){"\t", TK_BLANK, 1};
	ops[9] = (t_tk_ops){"\r", TK_BLANK, 1};
	ops[10] = (t_tk_ops){"\f", TK_BLANK, 1};
	ops[11] = (t_tk_ops){NULL, 0, 0};
}
/* Full list:

	ops[0] = (t_tk_ops){"<<", TK_HEREDOC, 2};
	ops[1] = (t_tk_ops){"<", TK_IN, 1};
	ops[2] = (t_tk_ops){">>", TK_OUT, 2};
	ops[3] = (t_tk_ops){">|", TK_OUT, 2};
	ops[4] = (t_tk_ops){"<>", TK_OUT, 2};
	ops[5] = (t_tk_ops){">", TK_OUT, 1};
	ops[6] = (t_tk_ops){"||", TK_OR, 2};
	ops[7] = (t_tk_ops){"&&", TK_AND, 2};
	ops[8] = (t_tk_ops){"(", TK_PARENTESHIS, 1};
	ops[9] = (t_tk_ops){")", TK_PARENTESHIS, 1};
	ops[10] = (t_tk_ops){"|", TK_PIPE, 1};
	ops[11] = (t_tk_ops){" ", TK_BLANK, 1};
	ops[12] = (t_tk_ops){"\n", TK_BLANK, 1};
	ops[13] = (t_tk_ops){"\v", TK_BLANK, 1};
	ops[14] = (t_tk_ops){"\t", TK_BLANK, 1};
	ops[15] = (t_tk_ops){"\r", TK_BLANK, 1};
	ops[16] = (t_tk_ops){"\f", TK_BLANK, 1};
	ops[17] = (t_tk_ops){NULL, 0, 0};
*/

/// @brief			Checks if the given character is a double quote
/// @param dq		Quote to check
/// @param tk		token to check
char	ft_get_dq(char dq, char tk)
{
	if (dq == '\'' && tk == '\'')
		return (0);
	if (dq == '\"' && tk == '\"')
		return (0);
	if (dq == 0 && tk == '\"')
		return ('\"');
	if (dq == 0 && tk == '\'')
		return ('\'');
	return (dq);
}

/** @} */
