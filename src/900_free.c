/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   900_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:12:55 by passunca          #+#    #+#             */
/*   Updated: 2024/07/07 11:16:23 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup free Free functions
* @{
*
* @brief		Free functions
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief		Handles freeing memory
/// @param sh	Array to be freed
void	ft_free_sh(t_shell *sh)
{
	if (sh)
	{
		ft_free_cmds(sh->cmds, sh->n_cmds);
		ft_free_arr(sh->envp);
		ft_free_arr(sh->path);
		free(sh->hostname);
		free(sh->home);
		free(sh->user);
		free(sh);
		rl_clear_history();
	}
}

/// @brief			Free array
/// @param arr		Array to be freed
/// @param status	Exit status
/// @var i			To iterate array members
/// @return			SUCCESS(0)
///					FAILURE(1)
int	ft_free_arr(char **arr)
{
	int	i;

	if (arr == NULL)
		return (FAILURE);
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (SUCCESS);
}

/// @brief			Free tokens
/// @param tk		Pointer to a list of t_token structs
/// @var tmp		Pointer to hold next token in the list
/// @return			SUCCESS(0)
///					FAILURE(1)
int	ft_free_tks(t_token **tk)
{
	t_token	*tmp;

	if (tk == NULL || *tk == NULL)
		return (FAILURE);
	while (*tk)
	{
		tmp = (*tk)->next;
		ft_free((*tk)->name);
		free(*tk);
		*tk = tmp;
	}
	return (SUCCESS);
}

/// @brief			Free commands
/// @param cmds		Pointer to an array of t_cmd structs
/// @param n_cmds	Number of commands in the array
/// @var i			To iterate through the array of commands
/// @var j			To iterate through the command's arguments
/// @return			SUCCESS(0)
///	@return			FAILURE(1)
/// @details
/// - Free command's arguments
/// - Free command argv
/// - Free command's input redirection
/// - Free command's output redirection
/// - Free command heredoc list
/// - Free command struct
/// @note			Used in ft_sh_loop() ...
int	ft_free_cmds(t_cmd *cmds, int n_cmds)
{
	int	i;
	int	j;

	if (cmds == NULL)
		return (FAILURE);
	i = -1;
	while (++i < n_cmds)
	{
		j = -1;
		while (++j < cmds[i].argc)
			if (cmds[i].argv[j])
				ft_free(cmds[i].argv[j]);
		free(cmds[i].argv);
		if (cmds[i].in)
			ft_vfree(cmds[i].in);
		if (cmds[i].out)
			ft_vfree(cmds[i].out);
	}
	ft_vfree(cmds);
	return (SUCCESS);
}

/// @brief			Free commands and tokens when no commands were parsed
/// @param cmds		Pointer to an array of t_cmd structs
/// @param n_cmds	Number of commands in the array
/// @param tks		Pointer to a list of t_token structs
///	@return			FAILURE(1)
/// @note			Used in ft_parser()
int	ft_free_nocmds(t_cmd *cmds, int n_cmds, t_token **tks)
{
	ft_free_cmds(cmds, n_cmds);
	ft_free_tks(tks);
	return (FAILURE);
}

/** @} */
