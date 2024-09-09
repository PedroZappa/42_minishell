/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:40:17 by passunca          #+#    #+#             */
/*   Updated: 2024/09/09 09:42:29 by passunca         ###   ########.fr       */
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
	if (sh == NULL)
		return (ft_err(MALLOC_ERR, errno), EXIT_FAILURE);
	if (ft_init(sh, envp) != SUCCESS)
		ft_err(INIT_ERR, errno);
	ft_sh_loop(sh);
	ft_free_sh(sh);
	return (EXIT_SUCCESS);
}

/// @brief			Minishell loop
/// @param sh		Pointer to a t_shell struct
/// @return			SUCCESS(status)
/// @note			Used in main()
static int	ft_sh_loop(t_shell *sh)
{
	char	*line_buf;
	int		status;

	status = SUCCESS;
	line_buf = NULL;
	while (1)
	{
		ft_sigset();
		status = ft_parser(sh, line_buf);
		if (status == FAILURE)
			continue ;
		sh->n_pipes = sh->n_cmds - (sh->n_cmds > 0);
		if (sh->n_cmds > NO_CMDS)
			if (ft_execute(sh) == FAILURE)
				break ;
		ft_free_cmds(sh->cmds, sh->n_cmds);
	}
	return (status);
}

/** @} */
