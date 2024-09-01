/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   750_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:24:56 by passunca          #+#    #+#             */
/*   Updated: 2024/07/20 17:21:40 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup main Main
* @{
*
* @brief		Minishell main function
* @version		1.0
***/

#include "../inc/minishell.h"

static int	ft_is_nflag(char *arg);
static char	*ft_rm_squotes(char *arg);

/// @brief			Echo built-in
/// @details
/// - Skip dash
/// - Check for 'n's (however many)
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_echo(t_shell *sh, int n)
{
	int	sentinel;
	int	i;

	ft_set_var("_", sh->cmds[n].argv[0], &sh->envp);
	i = 0;
	while (sh->cmds[n].argv[++i] && ft_is_nflag(sh->cmds[n].argv[i]))
		sentinel = '\0';
	if (sentinel == '\0')
		i = 2;
	while (sh->cmds[n].argv[i])
	{
		ft_putstr_fd(sh->cmds[n].argv[i], STDOUT_FILENO);
		if (sh->cmds[n].argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		++i;
	}
	ft_putchar_fd(sentinel, STDOUT_FILENO);
	return (SUCCESS);
}

/// @brief		Check for -n flag
/// @param arg	Argument to check
/// @return		SUCCESS(1)
/// @return		FAILURE(0)
static int	ft_is_nflag(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (!FAILURE);
	i = 0;
	while (arg[++i])
		if (arg[i] != 'n')
			return (!FAILURE);
	return (!SUCCESS);
}

/// @brief		Remove single quotes
/// @param arg	Argument to remove single quotes
/// @return		SUCCESS(unquoted string)
/// @return		FAILURE(NULL)
static char	*ft_rm_squotes(char *arg)
{
	char	*unquoted;
	int		len;

	len = ft_strlen(arg);
	unquoted = ft_substr(arg, 1, (len - 2));
	if (!unquoted)
		return (NULL);
	free(arg);
	return (unquoted);
}

/** @} */
