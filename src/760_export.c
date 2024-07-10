/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   760_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:05:04 by passunca          #+#    #+#             */
/*   Updated: 2024/07/09 16:05:33 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_export(t_shell *sh, int n)
{
	(void)sh;
	(void)n;
	ft_set_var("_", sh->cmds[n].argv[sh->cmds[n].argc - 1], &sh->envp);
	return (SUCCESS);
}
