/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   220_tk_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:54:18 by passunca          #+#    #+#             */
/*   Updated: 2024/07/13 12:46:27 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup tk_expander Token expander
* @{
*
* @brief		Token expander
* @version		1.0
***/

#include "../inc/minishell.h"

static char *ft_expand_var(t_shell *sh, char ***tkns);

/// @brief		Token expander
/// @details
/// - Initialize expander
/// - Expand variables
/// @param sh		Pointer to a t_shell struct
/// @param tkn_str	Pointer to token string
/// @return			Expanded token string
char	*ft_tk_expander(t_shell *sh, char *tk_str)
{
	char	**sub_tkns;
	char	*ret;
	int		curr_tk;
	int		i;

	sub_tkns = NULL;
	sub_tkns = ft_expander_init(tk_str);
	i = -1;
	curr_tk = i;
	while (tk_str[i])
	{
		++curr_tk;
		if (tk_str[i] == '$')
			sub_tkns[curr_tk] = ft_expand_dollar(tk_str, &i);
		else if (tk_str[i] == '\'')
			ft_expand_squote(&sub_tkns, tk_str, &i, &curr_tk);
		else if (tk_str[i] == '\"')
			ft_expand_dquote(&sub_tkns, tk_str, &i, &curr_tk);
	}
	ret = ft_expand_var(sh, &sub_tkns);
	free(sub_tkns);
	return (ret);
}

char	*ft_expand_dollar(char *tkn, int *i)
{
	char	*ret;
	int		tkn_start;

	tkn_start = *i;
	++(*i);
	if (tkn[*i] && (ft_check_alpha_c(tkn[*i]) == SUCCESS))
		while (tkn[*i] && (ft_check_alnum_c(tkn[*i]) == SUCCESS))
			++(*i);
	else if ((tkn[*i] != '\'') && (tkn[*i] != '\"'))
		++(*i);
	ret = ft_substr(tkn, tkn_start, (*i - tkn_start));
	return (ret);
}

void ft_expand_squote(char ***sub_tkns, char *tkn, int *i, int *curr_tk)
{
	(void)sub_tkns;
	(void)tkn;
	(void)i;
	(void)curr_tk;
}

void ft_expand_dquote(char ***sub_tkns, char *tkn, int *i, int *curr_tk)
{
	(void)tkn;
	(void)sub_tkns;
	(void)i;
	(void)curr_tk;
}

static char *ft_expand_var(t_shell *sh, char ***tkns)
{
	(void)sh;
	(void)tkns;
	return (NULL);
}
/** @} */
