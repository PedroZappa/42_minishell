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

// static int	ft_init(t_shell *sh, char **envp);
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

/// @brief		Initialize minishell
/// @param sh	Pointer to a t_shell struct
/// @param envp	Pointer to environment variables
/// @return		0 on success, 1 on failure.
/// @details	- Allocate memory for minishell
///				- Initialize envp
///				- Alloc memory for temp env
///				- Get HOME var
/// @note		Used in main()
// static int	ft_init(t_shell *sh, char **envp)
// {
// 	sh = ft_calloc(1, sizeof(t_shell));
// 	sh->envp = ft_init_env(envp);
// 	sh->envt = ft_calloc(1, sizeof(char *));
// 	if (!sh->envp || !sh->envt)
// 		return (ft_err(ENV_INIT_ERR, errno), FAILURE);
// 	sh->home = ft_get_var("HOME", sh->envp, NULL);
// 	sh->heredoc = ft_strdup("");
// 	ft_get_termios(STDIN_FILENO, &sh->termios);
// 	return (SUCCESS);
// }

/// @brief			Initialize env
/// @param env		Pointer to environment variables array
/// @var new_env	Pointer for memory allocation
/// @var n			Gets the count of environment variable
/// @return			Pointer to initialized env
/// @details		- Count variables
///					- Allocate memory
///					- Copy variables
/// @note			Used in ft_init()
static char	**ft_init_env(char **env)
{
	char	**new_env;
	int		n;

	n = 0;
	while (env[n])
		++n;
	new_env = ft_calloc((n + 1), sizeof(char *));
	if (!new_env)
		return (ft_err(MALLOC_ERR, errno), NULL);
	n = -1;
	while (env[++n])
	{
		new_env[n] = ft_strdup(env[n]);
		if (!new_env[n])
			return (NULL);
	}
	new_env[n] = NULL;
	return (new_env);
}
