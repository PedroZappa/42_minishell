/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:40:17 by passunca          #+#    #+#             */
/*   Updated: 2024/06/13 16:34:10 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @file			main.c
* @brief		Minishell main function
* @version		1.0
* @author		passunca & gfragoso
***/

#include "../inc/minishell.h"

static int	ft_init(t_shell *sh);
static char	**ft_init_env(char **env);

int	g_exit;

/// @brief		Minishell main function.
/// @param argc	Number of arguments.
/// @param argv	Array of arguments.
/// @param envp	Array of environment variables.
/// @return		0 on success, 1 on failure.
/// @details	- Init Env Variables
///				- Init Termios Interface
///				- Enter Minishell loop;
int	main(int argc, char **argv, char **envp)
{
	t_shell	*sh;

	(void)argc;
	(void)argv;
	(void)envp;
	sh = NULL;
	ft_printf("MINISHELL\n");
	ft_printf("Success : %d\n", SUCCESS);
	if (ft_init(sh) != SUCCESS)
		ft_err(INIT_ERR, errno);
	return (0);
}

/// @brief	
static int	ft_init(t_shell *sh)
{
	sh->cmds = NULL;
	sh->envp = NULL;
	sh->envp = ft_init_env(sh->envp);
	if (sh->envp != SUCCESS)
		return (ft_err(ENV_INIT_ERR, errno));
	sh->envt = NULL;
	sh->path = ft_strdup("");
	sh->home = ft_strdup("");
	sh->heredoc = ft_strdup("");
	ft_get_termios(STDIN_FILENO, &sh->termios);
	return (SUCCESS);
}

static char	**ft_init_env(char **env)
{
	char	**new_env;
	int		n;

	while (env[n])
		++n;
	new_env = ft_calloc((n + 1), sizeof(char *));
	if (new_env != SUCCESS)
		return (ft_err(MALLOC_ERR, errno), NULL);
	n = -1;
	while (env[++n])
	{
		new_env[n] = ft_strdup(env[n]);
		if (new_env != SUCCESS)
			return (NULL);
	}
	new_env[n] = NULL;
	return (new_env);
}
