/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   230_tk_expander_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:53:41 by passunca          #+#    #+#             */
/*   Updated: 2024/07/13 12:04:51 by passunca         ###   ########.fr       */
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

static char	*ft_expand_dollar_c(char *tkn, int *i);
static char	**ft_expand_squote_c(char *tkn, int *i);
static char	**ft_expand_dquote_c(char *tkn, int *n_tkns, int *i);
static char	**ft_expand_c(char *tkn, int *i);

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
			ft_expand_dollar_c(tkns, &i);
		else if (tkns[i] == '\'')
			ft_expand_squote_c(tkns, &i);
		else if (tkns[i] == '\"')
			ft_expand_dquote_c(tkns, &n_tkns, &i);
		else
			ft_expand_c(tkns, &i);
	}
	sub_tkns = ft_calloc((n_tkns + 1), sizeof(char *));
	if (!sub_tkns)
		return (ft_err(MALLOC_ERR, errno), NULL);
	sub_tkns[n_tkns] = NULL;
	return (sub_tkns);
}

static char	*ft_expand_dollar_c(char *tkn, int *i)
{
	(void)tkn;
	(void)i;
	return (NULL);
}

static char	**ft_expand_squote_c(char *tkn, int *i)
{
	(void)tkn;
	(void)i;
	return (NULL);
}

static char	**ft_expand_dquote_c(char *tkn, int *n_tkns, int *i)
{
	(void)tkn;
	(void)n_tkns;
	(void)i;
	return (NULL);
}

static char	**ft_expand_c(char *tkn, int *i)
{
	(void)tkn;
	(void)i;
	return (NULL);
}

/** @} */
