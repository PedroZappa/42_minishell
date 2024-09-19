/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   221_tk_expander2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:22:38 by gfragoso          #+#    #+#             */
/*   Updated: 2024/09/17 15:59:33 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @defgroup heredoc_expander Heredoc expander
* @{
*
* @brief		Heredoc expander
* @version		1.0
***/

#include "../inc/minishell.h"

int		ft_get_line_heredoc(t_list **list, char *delim);
char	*ft_expand_dollars(t_shell *sh, char *tkn);

char	*ft_heredoc_write(t_shell *sh, char *to_write)
{
	int		fd;
	char	*ret;

	if (to_write == NULL)
		return (NULL);
	ret = ft_redir_heredoc_name(sh->n_heredocs - 1);
	unlink(ret);
	fd = open(ret, O_CREAT | O_WRONLY | O_EXCL,
			S_IRWXU | S_IRGRP | S_IROTH);
	write(fd, to_write, ft_strlen(to_write));
	write(fd, "\n", 1);
	close(fd);
	return (ft_free(to_write), ret);
}

/// @brief		Heredoc expander
/// @param sh	Pointer to a t_shell struct
/// @param tkn	Pointer to token string
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
	ret = ft_compress_free_list(&list, '\n');
	if (expand)
		ret = ft_expand_dollars(sh, ret);
	return (ft_free(tkn), ft_heredoc_write(sh, ret));
}

/// @brief			Get heredoc line
/// @param list		Pointer to an array of t_list structs
/// @param delim	HereDoc Delimiter
int	ft_get_line_heredoc(t_list **list, char *delim)
{
	char	*ret;

	ret = readline(BWHT"> "NC);
	if (ret == NULL)
	{
		ft_printf("bash: warning: here-document at line "
			"%d delimited by end-of-file; (wanted '%s')\n",
			ft_lstsize(*list), delim);
		return (ft_free(delim), FAILURE);
	}
	if (ft_strcmp(ret, delim) == 0)
		return (ft_free(ret), ft_free(delim), FAILURE);
	if (*list == NULL)
		*list = ft_lstnew(ret);
	else
		ft_lstadd_back(list, ft_lstnew(ret));
	return (SUCCESS);
}

/// @brief		Dollar expansion
/// @param sh	Pointer to a t_shell struct
/// @param tkn	Pointer to token string
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
		ft_lstadd_back_ptr(&list, ft_expand_dollar(sh, tkn, &i, 0));
		tkn_start = i;
	}
	ft_lstadd_back_ptr(&list, ft_substr(tkn, tkn_start, i - tkn_start));
	i += 1;
	return (ft_free(tkn), ft_compress_free_list(&list, '\0'));
}

/** @} */
