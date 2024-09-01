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
char	*ft_expander(t_shell *sh, char *tk_str)
{
	int		i;
	int		j;
	char	*ret;
	char	*temp;

	i = 0;
	j = 0;
	ret = ft_strdup("");
	while (tk_str[i])
	{
		if (tk_str[i] == '\'')
		{
			ret = ft_strjoin_free(ret, ft_substr(tk_str, j, i - j));
			temp = ft_expand_squote(tk_str + i);
			i++;
			while (tk_str[i] && tk_str[i] != '\'')
				i++;
			ret = ft_strjoin_free(ret, temp);
			j = i;
			continue ;
		}
		if (tk_str[i] == '\"')
		{
			ret = ft_strjoin_free(ret, ft_substr(tk_str, j, i - j));
			temp = ft_expand_dquote(sh, tk_str + i);
			i++;
			while (tk_str[i] && tk_str[i] != '\"')
				i++;
			ret = ft_strjoin_free(ret, temp);
			j = i;
			continue ;
		}
		if (tk_str[i] == '$')
		{
			ret = ft_strjoin_free(ret, ft_substr(tk_str, j, i - j));
			temp = ft_expand_dollar(sh, tk_str + i);
			i++;
			while (tk_str[i] && ft_check_alnum(tk_str[i]))
				i++;
			ret = ft_strjoin_free(ret, temp);
			j = i;
			continue ;
		}
		i++;
	}
	ret = ft_strjoin_free(ret, ft_substr(tk_str, j, i - j));
	return (ft_free(tk_str), ret);
}

/// @brief		Dollar sign expansion
/// @param tkn	Token string
/// @param i	Reference to index
/// @return		Expanded token
char	*ft_expand_dollar(t_shell *sh, char *tkn)
{
	int		i;
	char	*ret;

	i = 1;
	if (tkn[i] && (ft_check_alpha(tkn[i]) == SUCCESS))
	{
		while (tkn[i] && (ft_check_alnum(tkn[i]) == SUCCESS))
			i++;
	}
	else
		return (ft_strdup("$"));
	if (tkn[i] != '\0')
		return (NULL);
	ret = ft_fill_var(sh, tkn);
	if (ret == NULL)
		ret = ft_strdup("");
	return (ret);
}

char	*ft_expand_squote(char *tkn)
{
	int		i;
	char	*ret;

	i = 1;
	while (tkn[i] && tkn[i] != '\'')
		i++;
	if (tkn[i] != '\'')
		return (NULL);
	ret = ft_substr(tkn, 1, i - 1);
	return (ret);
}

char	*ft_expand_dquote(t_shell *sh, char *tkn)
{
	int		i;
	int		j;
	char	*ret;
	char	*temp;

	i = 1;
	j = 1;
	ret = ft_strdup("");
	while (tkn[i] && (tkn[i] != '\"'))
	{
		if (tkn[i] == '$')
		{
			ret = ft_strjoin_free(ret, ft_substr(tkn, j, i - j));
			j = i + 1;
			if (tkn[j] && (ft_check_alpha(tkn[j]) == SUCCESS))
				while (tkn[j] && (ft_check_alnum(tkn[j]) == SUCCESS))
					j++;
			temp = ft_expand_dollar(sh, ft_substr(tkn, i, j - i));
			ret = ft_strjoin_free(ret, temp);
			i = j;
			continue ;
		}
		i++;
	}
	ret = ft_strjoin_free(ret, ft_substr(tkn, j, i - j));
	if (tkn[i] != '\"')
	{
		ft_free(ret);
		return (NULL);
	}
	return (ret);
}

/** @} */
