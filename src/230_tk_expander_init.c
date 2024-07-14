/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   230_tk_expander_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:53:41 by passunca          #+#    #+#             */
/*   Updated: 2024/07/13 21:41:24 by passunca         ###   ########.fr       */
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

static void	ft_expand_check_dollar(char *tkn, int *i);
static void	ft_expand_check_squote(char *tkn, int *i);
static void	ft_expand_check_dquote(char *tkn, int *n_tkns, int *i);
static void	ft_expand_check_other(char *tkn, int *i);

/// @brief			Gets the numnber of tokens for expansion
/// @param tkns		Token string
/// @return			Alloced array of sub-tokens
char **ft_expander_init(char *tkns)
{
	char	**sub_tkns;
	int		n_tkns;
	int		i;

	i = 0;
	n_tkns = 0;
	while (tkns[i])
	{
		n_tkns++;
		if (tkns[i] == '$')
			ft_expand_check_dollar(tkns, &i);
		else if (tkns[i] == '\'')
			ft_expand_check_squote(tkns, &i);
		else if (tkns[i] == '\"')
			ft_expand_check_dquote(tkns, &n_tkns, &i);
		else
			ft_expand_check_other(tkns, &i);
	}
	sub_tkns = ft_calloc((n_tkns + 1), sizeof(char *));
	if (!sub_tkns)
		return (ft_err(MALLOC_ERR, errno), NULL);
	sub_tkns[n_tkns] = NULL;
	return (sub_tkns);
}

/// @brief		Dollar sign expansion
/// @param tkn	Token string
/// @param i	Index
/// @return		Expansion string
static void	ft_expand_check_dollar(char *tkn, int *i)
{
	++(*i);
	if (tkn[*i] && (ft_check_alpha(tkn[*i]) == SUCCESS))
		while (tkn[*i] && (ft_check_alnum(tkn[*i]) == SUCCESS))
			++(*i);
	else if ((tkn[*i] != '\'') && (tkn[*i] != '\"'))
		++(*i);
}

static void	ft_expand_check_squote(char *tkn, int *i)
{
	++(*i);
	while (tkn[*i] && (tkn[*i] != '\''))
		++(*i);
	++(*i);
}

static void	ft_expand_check_dquote(char *tkn, int *n_tkns, int *i)
{
	(void)tkn;
	(void)n_tkns;
	(void)i;
}

static void	ft_expand_check_other(char *tkn, int *i)
{
	++(*i);
	while (tkn[*i] && (tkn[*i] != '$')
		&& (tkn[*i] != '\'') && (tkn[*i] != '\"'))
		++(*i);
}

/** @} */
