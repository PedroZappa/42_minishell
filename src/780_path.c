/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   780_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:41:46 by gfragoso          #+#    #+#             */
/*   Updated: 2024/08/09 11:45:11 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @defgroup 	path Path
* @{
*
* @brief		Check if path exists
* @version		1.0
***/

#include "../inc/minishell.h"


int	ft_path(t_shell *sh, int n)
{
	t_stat	sb;
	int		stat_ret;

	memset(&sb, 0, sizeof(t_stat));
	stat_ret = stat(sh->cmds[n].argv[0], &sb);
	if ((sb.st_mode & __S_IFMT) == __S_IFDIR)
		ft_fprintf(STDOUT_FILENO, "bash: %s: Is a directory\n",
			sh->cmds[n].argv[0]);
	if (stat_ret == -1)
		ft_fprintf(STDERR_FILENO, "bash: %s: No such file or directory\n",
			sh->cmds[n].argv[0]);
	return (stat_ret);
}
