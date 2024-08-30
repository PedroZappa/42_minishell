/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   240_tk_expander_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:14:40 by passunca          #+#    #+#             */
/*   Updated: 2024/07/18 17:07:58 by passunca         ###   ########.fr       */
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

static char	*ft_fill_var(t_shell *sh, char *tkn);
static char	*ft_unquote(char *tkn);

/// @brief			Initialize expander
/// @details
/// - Allocate emptry return string
///- Loop through tokens
///		- If token is $, expand
///		- else handle single and double quotes  TODO:
///		- Join expanded token to return string
/// @param sh		Pointer to a t_shell struct
/// @param sub_tkns	Pointer to array of token strings
char	*ft_expand_var(t_shell *sh, char ***sub_tkns)
{
	char	*ret;
	char	*curr;
	int		i;

	ret = ft_strdup("");
	i = 0;
	while ((*sub_tkns)[i])
	{
		curr = (*sub_tkns)[i];
		if (((*sub_tkns)[i][0] == '$') \
			&& ((*sub_tkns)[i][1] || (*sub_tkns)[i + 1]))
		{
			(*sub_tkns)[i] = ft_fill_var(sh, curr);
			if ((*sub_tkns)[i] == NULL)
				(*sub_tkns)[i] = ft_strdup("");
		}
		else
			(*sub_tkns)[i] = ft_unquote(curr);
		ret = ft_strjoin_free(ret, (*sub_tkns)[i]);
		++i;
	}
	return (ret);
}

/// @brief			Fill expanded variable
/// @details
/// Conditionally extract variable
/// - If first character is a letter or _ get var from env
/// - If it is ?, get exit code
/// - Else, return the string
/// @param sh		Pointer to a t_shell struct
/// @param tkn		Token string
static char	*ft_fill_var(t_shell *sh, char *tkn)
{
	char	*var;
	int		i;

	i = 1;
	var = NULL;
	if (ft_check_alpha(tkn[i]) == SUCCESS)
		var = ft_get_var((tkn + 1), sh->envp, sh->envt);
	else if (tkn[i] == '?')
		var = ft_itoa(WEXITSTATUS(g_exit));
	else
		var = ft_strdup(tkn);
	// TODO: Other Else ifs ...
	ft_free(tkn);
	return (var);
}

/// @brief			Unquote single and double quotes
/// @param tkn		Token string
/// @return			Unquoted string
static char	*ft_unquote(char *tkn)
{
	char	*ret;
	int		len;

	ret = NULL;
	len = ft_strlen(tkn);
	if (tkn[0] == '\'' && (tkn[(len - 1)] == '\"'))
		ret = ft_substr(tkn, 0, (len - 1));
	else if ((tkn[0] == '\'') || ((tkn[0] == '\"')
			&& (tkn[(len - 1)] == '\"')))
		ret = ft_substr(tkn, 1, (len - 2));
	else if (tkn[0] != '\"' && (tkn[(len - 1)] == '\"'))
		ret = ft_substr(tkn, 0, (len - 1));
	else
		ret = ft_strdup(tkn);
	ft_free(tkn);
	return (ret);
}

/** @} */
