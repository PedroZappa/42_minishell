/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:40:17 by passunca          #+#    #+#             */
/*   Updated: 2024/06/22 09:59:44 by passunca         ###   ########.fr       */
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

static int	ft_sh_loop(t_shell *sh);

int	g_exit;

/// @brief		Minishell main function.
/// @details
/// - Init Env Variables
/// - Init Termios Interface
/// - Enter Minishell loop;
/// @param argc	Number of arguments.
/// @param argv	Array of arguments.
/// @param envp	Array of environment variables.
/// @return		SUCCESS(0)
///	@return		FAILURE(1)
int	main(int argc, char **argv, char **envp)
{
	t_shell	*sh;

	(void)argc;
	(void)argv;
	sh = ft_calloc(1, sizeof(t_shell));
	if (!sh)
		return (ft_err(MALLOC_ERR, errno), EXIT_FAILURE);
	if (ft_init(sh, envp) != SUCCESS)
		ft_err(INIT_ERR, errno);
	ft_sh_loop(sh);
	ft_free_sh(sh);
	return (EXIT_SUCCESS);
}

/// @brief			Minishell loop
/// @details
/// - Setup signal handler
/// - Call parser
/// - Execute commands
/// @param sh		Pointer to a t_shell struct
/// @var line_buf	Line buffer
/// @var status		Stores parser exit status
/// @return			SUCCESS(status)
///	@return			FAILURE(1)
/// @note			Used in main()
static int	ft_sh_loop(t_shell *sh)
{
	char	*line_buf;
	int		status;

	(void)sh;
	status = 0;
	line_buf = NULL;
	while (1)
	{
		ft_sigset();
		status = ft_parser(sh, &line_buf);
		ft_free(line_buf);
		if (status == FAILURE)
			continue ;
		if (sh->n_cmds > NO_CMDS)
			if (ft_execute(sh) == FAILURE)
				break ;
		ft_free_cmds(sh->cmds, sh->n_cmds);
	}
	return (status);
}

/** @} */
