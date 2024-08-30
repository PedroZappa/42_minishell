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
	sh->hostname = ft_get_hostname();
	ft_set_var("OLDPWD", NULL, &sh->envp);
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

char	*ft_get_hostname(void)
{
	int		fd;
	char	*ret;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("42"));
	ret = get_next_line(fd);
	ret[ft_strlen(ret) - 1] = '\0';
	return (ret);
}
/** @} */
