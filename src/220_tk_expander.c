/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   220_tk_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:54:18 by passunca          #+#    #+#             */
/*   Updated: 2024/07/13 22:01:28 by passunca         ###   ########.fr       */
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
static char	*ft_fill_var(t_shell *sh, char *tkn);

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
	i = 0;
	curr_tk = -1;
	while (tk_str[i])
	{
		++curr_tk;
		if (tk_str[i] == '$')
			sub_tkns[curr_tk] = ft_expand_dollar(tk_str, &i);
		else if (tk_str[i] == '\'')
			ft_expand_squote(&sub_tkns, tk_str, &i, &curr_tk);
		else if (tk_str[i] == '\"')
			ft_expand_dquote(&sub_tkns, tk_str, &i, &curr_tk);
		else
			ft_expand_other(&sub_tkns, tk_str, &i, &curr_tk);
	}
	ret = ft_expand_var(sh, &sub_tkns);
	free(sub_tkns);
	return (ret);
}

/// @brief		Dollar sign expansion
/// @param tkn	Token string
/// @param i	Reference to index
/// @return		Expanded token
char	*ft_expand_dollar(char *tkn, int *i)
{
	int		tkn_start;
	int		tkn_len;
	char	*ret;

	tkn_start = *i;
	++(*i);
	if (tkn[*i] && (ft_check_alpha(tkn[*i]) == SUCCESS))
		while (tkn[*i] && (ft_check_alnum(tkn[*i]) == SUCCESS))
			++(*i);
	else if ((tkn[*i] != '\'') && (tkn[*i] != '\"'))
		++(*i);
	tkn_len = (*i - tkn_start);
	ret = ft_substr(tkn, tkn_start, tkn_len);
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

/// @brief			Save unexpanded token
/// @param sub_tkns	Pointer to array of sub-tokens
/// @param tkn		Token string
/// @param i		Reference to index
/// @param curr_tk	Current token
void ft_expand_other(char ***sub_tkns, char *tkn, int *i, int *curr_tk)
{
	int	tkn_start;
	int	tkn_len;

	tkn_start = *i;
	(*i)++;
	while (tkn[*i] && (tkn[*i] != '$')
		&& (tkn[*i] != '\'') && (tkn[*i] != '\"'))
		++(*i);
	tkn_len = (*i - tkn_start);
	(*sub_tkns)[(*curr_tk)] = ft_substr(tkn, tkn_start, tkn_len);

}

/// @brief			Initialize expander
/// @details
/// - Allocate emptry return string
///- Loop through tokens
///		- If token is $, expand
///		- else handle single and double quotes  TODO:
///		- Join expanded token to return string
/// @param sh		Pointer to a t_shell struct
/// @param sub_tkns	Pointer to array of token strings
static char *ft_expand_var(t_shell *sh, char ***sub_tkns)
{
	char	*ret;
	char	*curr;
	int		i;

	ret = ft_strdup("");
	i = -1;
	while ((*sub_tkns)[++i])
	{
		curr = (*sub_tkns)[i];
		if ((*sub_tkns)[i][0] == '$')
		{
			(*sub_tkns)[i] = ft_fill_var(sh, curr);
			if (!(*sub_tkns)[i])
				(*sub_tkns)[i] = ft_strdup("");
		}
		// TODO: Else Handle Single & Double Quotes
		ret = ft_strjoin_free(ret, (*sub_tkns)[i]);
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

/** @} */
