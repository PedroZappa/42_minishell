/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:40:17 by passunca          #+#    #+#             */
/*   Updated: 2024/06/19 11:53:58 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @file			main.c
* @brief		Minishell main function
* @version		1.0
* @author		passunca & gfragoso
***/

#include "../inc/minishell.h"

// static int	ft_sh_loop(t_shell *sh);

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
	if (!sh)
		return (ft_err(MALLOC_ERR, errno), FAILURE);
	if (ft_init(sh, envp) != SUCCESS)
		ft_err(INIT_ERR, errno);
	// ft_sh_loop(sh);
	ft_free_sh(sh, SUCCESS);
	return (EXIT_SUCCESS);
}

int	ft_init(t_shell *sh, char **envp)
{
	sh->envp = ft_init_env(envp);
	sh->envt = ft_calloc(1, sizeof(char *));
	if (!sh->envp || !sh->envt)
		return (ft_err(ENV_INIT_ERR, errno), FAILURE);
	sh->home = ft_get_var("HOME", sh->envp, NULL);
	sh->heredoc = ft_strdup("");
	ft_get_termios(STDIN_FILENO, &sh->termios);
	return (SUCCESS);
}

// static int	ft_sh_loop(t_shell *sh)
// {
// 	char	*line_buf;
// 	int		status;
//
// 	(void)sh;
// 	status = 0;
// 	line_buf = NULL;
// 	while (1)
// 	{
// 		// ft_sigset();
// 		// status = ft_parser(sh, &line_buf);
// 	}
// }
