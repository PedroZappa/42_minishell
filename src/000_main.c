/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:40:17 by passunca          #+#    #+#             */
/*   Updated: 2024/06/14 23:27:30 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @file			main.c
* @brief		Minishell main function
* @version		1.0
* @author		passunca & gfragoso
***/

#include "../inc/minishell.h"

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
	sh = ft_calloc(1, sizeof(t_shell));
	sh->envp = ft_init_env(envp);
	sh->envt = ft_calloc(1, sizeof(char *));
	if (!sh->envp || !sh->envt)
		return (ft_err(ENV_INIT_ERR, errno), FAILURE);
	sh->home = ft_get_var("HOME", sh->envp, NULL);
	sh->heredoc = ft_strdup("");
	ft_get_termios(STDIN_FILENO, &sh->termios);
	ft_free_arr(sh->envp, 0);
	ft_free_arr(sh->envt, 0);
	ft_free_arr(sh->path, 0);
	ft_free_sh(sh, SUCCESS);
	return (EXIT_SUCCESS);
}
