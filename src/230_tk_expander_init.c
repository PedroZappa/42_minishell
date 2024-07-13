/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   230_tk_expander_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:53:41 by passunca          #+#    #+#             */
/*   Updated: 2024/07/13 12:28:17 by passunca         ###   ########.fr       */
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

static void	ft_expander_check_dollar_c(char *tkn, int *i);
static void	ft_expander_check_squote_c(char *tkn, int *i);
static void	ft_expander_check_dquote_c(char *tkn, int *n_tkns, int *i);
static void	ft_expander_check_c(char *tkn, int *i);

/// @brief			Token expander initializer
/// @param tkns		Token string
///
char **ft_expander_init(char *tkns)
{
	char	**sub_tkns;
	int		n_tkns;
	int		i;

	n_tkns = -1;
	i = 0;
	while (tkns[i])
	{
		++n_tkns;
		if (tkns[i] == '$')
			ft_expander_check_dollar_c(tkns, &i);
		else if (tkns[i] == '\'')
			ft_expander_check_squote_c(tkns, &i);
		else if (tkns[i] == '\"')
			ft_expander_check_dquote_c(tkns, &n_tkns, &i);
		else
			ft_expander_check_c(tkns, &i);
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
static void	ft_expander_check_dollar_c(char *tkn, int *i)
{
	++(*i);
	if (tkn[*i] && (ft_check_alpha_c(tkn[*i]) == SUCCESS))
		while (tkn[*i] && (ft_check_alnum_c(tkn[*i]) == SUCCESS))
			++(*i);
	else if ((tkn[*i] != '\'') && (tkn[*i] != '\"'))
		++(*i);
}

static void	ft_expander_check_squote_c(char *tkn, int *i)
{
	(void)tkn;
	(void)i;
}

static void	ft_expander_check_dquote_c(char *tkn, int *n_tkns, int *i)
{
	(void)tkn;
	(void)n_tkns;
	(void)i;
}

static void	ft_expander_check_c(char *tkn, int *i)
{
	(void)tkn;
	(void)i;
}

/** @} */
