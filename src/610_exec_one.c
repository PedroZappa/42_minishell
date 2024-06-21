/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   610_exec_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:51:40 by passunca          #+#    #+#             */
/*   Updated: 2024/06/21 20:58:12 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @file			610_exec_one.c
* @brief		Execute one command
* @version		1.0
* @author		passunca
***/

#include "../inc/minishell.h"

static int	ft_exec_fork(t_shell *sh);

int	ft_exec_one(t_shell *sh, t_cmd *cmd)
{
	(void)sh;
	(void)cmd;
	return (SUCCESS);
}

static int	ft_exec_fork(t_shell *sh)
{
	(void)sh;
	return (SUCCESS);
}
