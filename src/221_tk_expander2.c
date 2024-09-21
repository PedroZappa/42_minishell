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

int	ft_heredoc_write(t_shell *sh, char *to_write)
{
	int		fd;
	char	*ret;

	if (to_write == NULL)
		return (FAILURE);
	ret = ft_redir_heredoc_name(sh->n_heredocs - 1);
	if (ret == NULL)
		return (ft_free(to_write), FAILURE);
	unlink(ret);
	fd = open(ret, O_CREAT | O_WRONLY | O_EXCL,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (FAILURE);
	write(fd, to_write, ft_strlen(to_write));
	write(fd, "\n", 1);
	close(fd);
	return (ft_free(to_write), ft_free(ret), SUCCESS);
}

/// @brief		Heredoc expander
/// @param sh	Pointer to a t_shell struct
/// @param tkn	Pointer to token string
int	ft_heredoc_expander_fork(t_shell *sh, t_token *tk, char *tkn)
{
	t_hd_vars	hd;
	int			expand;

	hd.list = NULL;
	hd.tk = tk;
	hd.ret = ft_strdup(tkn);
	hd.delim = ft_expander(sh, hd.ret);
	expand = ft_strcmp(tkn, hd.delim) == 0;
	hd.ret = NULL;
	ft_heredoc_sighandler(-1, sh, &hd);
	while (ft_get_line_heredoc(&hd.list, hd.delim) == 0)
		;
	hd.ret = ft_compress_free_list(&hd.list, '\n');
	hd.list = NULL;
	if (expand)
		hd.ret = ft_expand_dollars(sh, hd.ret);
	return (ft_free(hd.delim), ft_heredoc_write(sh, hd.ret));
}

int	ft_heredoc_expander(t_shell *sh, t_token *tk, char *tkn)
{
	int	pid;

	pid = fork();
	if (pid == PID_FAIL)
		return (ft_err(FORK_ERR, errno), FAILURE);
	ft_sigignore();
	if (pid == SUCCESS)
	{
		ft_heredoc_sigset();
		ft_heredoc_expander_fork(sh, tk, tkn);
		ft_free_tks(&tk);
		ft_free_sh_partial(sh);
		exit(0);
	}
	wait(&g_exit);
	ft_sigset();
	if (g_exit == 0)
		ft_free(tkn);
	return (g_exit);
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
		return (FAILURE);
	}
	if (ft_strcmp(ret, delim) == 0)
		return (ft_free(ret), FAILURE);
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
