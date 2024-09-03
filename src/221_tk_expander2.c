/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   221_tk_expander2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:22:38 by gfragoso          #+#    #+#             */
/*   Updated: 2024/09/02 23:17:21 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		ft_get_line_heredoc(t_list **list, char *delim);
char	*ft_expand_dollars(t_shell *sh, char *tkn);

char	*ft_heredoc_expander(t_shell *sh, char *tkn)
{
	char	*delim;
	char	*ret;
	int		expand;
	t_list	*list;
	int		exit;

	list = NULL;
	ret = ft_strdup(tkn);
	delim = ft_expander(sh, ret);
	expand = ft_strcmp(tkn, delim) == 0;
	exit = 0;
	while (exit == 0)
		exit = ft_get_line_heredoc(&list, delim);
	if (exit == -1)
		return (ft_lstclear(&list, free), ft_free(tkn), NULL);
	ret = ft_compress_free_list(&list, '\n');
	if (expand)
		ret = ft_expand_dollars(sh, ret);
	return (ret);
}

int	ft_get_line_heredoc(t_list **list, char *delim)
{
	char	*ret;

	ret = readline(BWHT"> "NC);
	if (ret == NULL)
		return (-1);
	if (ft_strcmp(ret, delim) == 0)
		return (ft_free(ret), 1);
	if (*list == NULL)
		*list = ft_lstnew(ret);
	else
		ft_lstadd_back(list, ft_lstnew(ret));
	return (0);
}

char	*ft_expand_dollars(t_shell *sh, char *tkn)
{
	int		tkn_start;
	t_list	*list;
	int		i;

	list = ft_lstnew(ft_strdup(""));
	i = 0;
	tkn_start = 0;
	while (tkn[i])
	{
		if (tkn[i] != '$')
		{
			i += 1;
			continue ;
		}
		ft_lstadd_back_ptr(&list, ft_substr(tkn, tkn_start, i - tkn_start));
		ft_lstadd_back_ptr(&list, ft_expand_dollar(sh, tkn, &i));
		tkn_start = i;
	}
	ft_lstadd_back_ptr(&list, ft_substr(tkn, tkn_start, i - tkn_start));
	i += 1;
	return (ft_free(tkn), ft_compress_free_list(&list, '\0'));
}
