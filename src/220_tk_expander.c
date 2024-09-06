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
/// @param sh		Pointer to a t_shell struct
/// @param tkn		Pointer to token string
/// @return			Expanded token string
char	*ft_expander(t_shell *sh, char *tkn)
{
	int		i;
	int		tkn_start;
	t_list	*list;

	list = ft_lstnew(ft_strdup(""));
	i = 0;
	tkn_start = 0;
	while (tkn[i])
	{
		if (tkn[i] != '$' && tkn[i] != '\'' && tkn[i] != '\"')
		{
			i++;
			continue ;
		}
		ft_lstadd_back_ptr(&list, ft_substr(tkn, tkn_start, i - tkn_start));
		if (tkn[i] == '$')
			ft_lstadd_back_ptr(&list, ft_expand_dollar(sh, tkn, &i));
		else if (tkn[i] == '\'')
			ft_lstadd_back_ptr(&list, ft_expand_squote(tkn, &i));
		else
			ft_lstadd_back_ptr(&list, ft_expand_dquote(sh, tkn, &i));
		tkn_start = i;
	}
	ft_lstadd_back_ptr(&list, ft_substr(tkn, tkn_start, i - tkn_start));
	return (ft_free(tkn), ft_compress_free_list(&list, '\0'));
}

/// @brief		Single quote expansion
/// @param tkn	Token string
/// @param i	Reference to index
/// @return		SUCCESS(Expanded token)
char	*ft_expand_squote(char *tkn, int *i)
{
	char	*ret;
	int		tkn_start;

	*i += 1;
	tkn_start = *i;
	while (tkn[*i] && tkn[*i] != '\'')
		*i += 1;
	if (tkn[*i] != '\'')
		return (NULL);
	ret = ft_substr(tkn, tkn_start, *i - tkn_start);
	*i += 1;
	return (ret);
}

/// @brief		Dollar sign expansion
/// @param sh	Pointer to a t_shell struct
/// @param tkn	Token string
/// @param i	Reference to index
/// @return		Expanded token
char	*ft_expand_dollar(t_shell *sh, char *tkn, int *i)
{
	char	*ret;
	char	*temp;
	int		tkn_start;

	tkn_start = *i;
	*i += 1;
	if (tkn[*i] && (ft_check_alpha(tkn[*i]) == 0))
	{
		while (tkn[*i] && (ft_check_alnum(tkn[*i]) == 0))
			*i += 1;
	}
	else if (tkn[*i] == '?' || ft_isdigit(tkn[*i]))
		*i += 1;
	else if ((tkn[*i] == '\'' || tkn[*i] == '\"') && tkn[*i + 1] != '\0')
		return (ft_strdup(""));
	else
		return (ft_strdup("$"));
	temp = ft_substr(tkn, tkn_start, (*i - tkn_start));
	ret = ft_fill_var(sh, temp);
	if (ret == NULL)
		ret = ft_strdup("");
	return (ft_free(temp), ret);
}

/// @brief		Double quote expansion
/// @param sh	Pointer to a t_shell struct
/// @param tkn	Token string
/// @param i	Reference to index
/// @return		Expanded token
char	*ft_expand_dquote(t_shell *sh, char *tkn, int *i)
{
	int		tkn_start;
	char	*ret;

	ret = ft_strdup("");
	*i += 1;
	tkn_start = *i;
	while (tkn[*i] && tkn[*i] != '\"')
	{
		if (tkn[*i] != '$')
		{
			*i += 1;
			continue ;
		}
		ret = ft_strjoin_free(ret, ft_substr(tkn, tkn_start, *i - tkn_start));
		ret = ft_strjoin_free(ret, ft_expand_dollar(sh, tkn, i));
		tkn_start = *i;
	}
	if (tkn[*i] != '\"')
		return (ft_free(ret), NULL);
	ret = ft_strjoin_free(ret, ft_substr(tkn, tkn_start, *i - tkn_start));
	*i += 1;
	return (ret);
}

/** @} */
