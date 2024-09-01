/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   220_tk_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:54:18 by passunca          #+#    #+#             */
/*   Updated: 2024/07/20 21:35:33 by passunca         ###   ########.fr       */
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

/// @brief		Token expander
/// @details
/// - Initialize expander
/// - Expand variables
/// @param sh		Pointer to a t_shell struct
/// @param tkn_str	Pointer to token string
/// @return			Expanded token string
char	*ft_expander(t_shell *sh, char *tkn)
{
	int		i;
	int		j;
	char	*ret;

	ret = ft_strdup("");
	i = 0;
	j = 0;
	while (tkn[i])
	{
		if (tkn[i] != '$' && tkn[i] != '\'' && tkn[i] != '\"')
		{
			i++;
			continue ;
		}
		ret = ft_strjoin_free(ret, ft_substr(tkn, j, i - j));
		if (tkn[i] == '$')
			ret = ft_strjoin_free(ret, ft_expand_dollar(sh, tkn, &i));
		else if (tkn[i] == '\'')
			ret = ft_strjoin_free(ret, ft_expand_squote(tkn, &i));
		else
			ret = ft_strjoin_free(ret, ft_expand_dquote(sh, tkn, &i));
		j = i;
	}
	ret = ft_strjoin_free(ret, ft_substr(tkn, j, i - j));
	return (ft_free(tkn), ret);
}

char	*ft_expand_squote(char *tkn, int *i)
{
	char	*ret;
	int		j;

	*i += 1;
	j = *i;
	while (tkn[*i] && tkn[*i] != '\'')
		*i += 1;
	if (tkn[*i] != '\'')
		return (NULL);
	ret = ft_substr(tkn, j, *i - j);
	*i += 1;
	return (ret);
}

/// @brief		Dollar sign expansion
/// @param tkn	Token string
/// @param i	Reference to index
/// @return		Expanded token
char	*ft_expand_dollar(t_shell *sh, char *tkn, int *i)
{
	char	*ret;
	char	*temp;
	int		j;

	j = *i;
	*i += 1;
	if (tkn[*i] && (ft_check_alpha(tkn[*i]) == 0))
	{
		while (tkn[*i] && (ft_check_alnum(tkn[*i]) == 0))
			*i += 1;
	}
	else if (tkn[*i] == '?')
		*i += 1;
	else if ((tkn[*i] == '\'' || tkn[*i] == '\"') && tkn[*i + 1] != '\0')
		return (ft_strdup(""));
	else
		return (ft_strdup("$"));
	temp = ft_substr(tkn, j, *i - j);
	ret = ft_fill_var(sh, temp);
	if (ret == NULL)
		ret = ft_strdup("");
	return (ft_free(temp), ret);
}

char	*ft_expand_dquote(t_shell *sh, char *tkn, int *i)
{
	int		j;
	char	*ret;

	ret = ft_strdup("");
	*i += 1;
	j = *i;
	while (tkn[*i] && tkn[*i] != '\"')
	{
		if (tkn[*i] != '$')
		{
			*i += 1;
			continue ;
		}
		ret = ft_strjoin_free(ret, ft_substr(tkn, j, *i - j));
		ret = ft_strjoin_free(ret, ft_expand_dollar(sh, tkn, i));
		j = *i;
	}
	if (tkn[*i] != '\"')
		return (ft_free(ret), NULL);
	ret = ft_strjoin_free(ret, ft_substr(tkn, j, *i - j));
	*i += 1;
	return (ret);
}

/** @} */
