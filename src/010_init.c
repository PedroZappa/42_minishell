/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   010_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:53:41 by passunca          #+#    #+#             */
/*   Updated: 2024/08/08 12:10:37 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @defgroup init Init
* @{
*
* @brief		Initialize minishell
* @version		1.0
***/

#include "../inc/minishell.h"

static void	ft_shlvl(t_shell *sh);

/// @brief		Initialize minishell
/// @details
///	- Allocate memory for minishell
///	- Initialize envp (primary env)
///	- Alloc envt (temporary env)
///	- Get HOME var
///	- Initialize heredoc
///	- Get snapshot of termios interface state
///	- Set readline() editing mode to VI
/// @param sh	Pointer to a t_shell struct
/// @param envp	Pointer to environment variables
/// @return		SUCCESS(0)
///				FAILURE(1)
/// @note		Used in main()
int	ft_init(t_shell *sh, char **envp)
{
	sh->envp = ft_init_env(envp);
	ft_shlvl(sh);
	sh->envt = ft_calloc(1, sizeof(char *));
	if (sh->envp == NULL || sh->envt == NULL)
		return (ft_err(ENV_INIT_ERR, errno), FAILURE);
	sh->home = ft_get_var("HOME", sh->envp, NULL);
	sh->user = ft_get_var("USER", sh->envp, NULL);
	ft_set_var("OLDPWD", NULL, &sh->envp);
	// sh->heredoc = ft_strdup("");
	ft_get_termios(STDIN_FILENO, &sh->termios);
	rl_editing_mode = VI;
	sh->n_pipes = 0;
	return (SUCCESS);
}

/// @brief		Initialize shell level
/// @param sh	Pointer to a t_shell struct
/// @note		Used in main()
static void	ft_shlvl(t_shell *sh)
{
	static int	lvl;
	char		*shlvl;
	char		*new;
	int			i;

	lvl = 0;
	shlvl = ft_get_var("SHLVL", sh->envp, NULL);
	if (shlvl)
	{
		if (lvl == 0)
		{
			lvl = 1;
			i = ft_atoi(shlvl);
		}
		else
			i = (ft_atoi(shlvl) + 1);
		new = ft_itoa(i);
		if (new == NULL)
			ft_err(MALLOC_ERR, errno);
		ft_set_var("SHLVL", new, &sh->envp);
		free(new);
		free(shlvl);
	}
	else
		ft_set_var("SHLVL", "1", &sh->envp);
}

/** @} */

/// @brief Initialize in & out redirections
/// @param cmds Pointer to an array of t_cmd structs
/// @param n_cmds Number of commands in the array
/// @note		Used in ft_parser()
void	ft_reset_redir(t_cmd *cmds, int n_cmds)
{
	int	i;

	i = -1;
	while (++i < n_cmds)
	{
		cmds[i].in.name = NULL;
		cmds[i].in.heredoc = NULL;
		cmds[i].in.flag = -1;
		cmds[i].out.name = NULL;
		cmds[i].out.flag = -1;
	}
}
