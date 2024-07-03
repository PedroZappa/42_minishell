/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   310_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:46:35 by passunca          #+#    #+#             */
/*   Updated: 2024/07/03 14:36:02 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
* @defgroup 	readline Readline
* @{
*
* @brief		Readline functionality
* @version		1.0
***/

#include "../inc/minishell.h"

static char	*ft_get_prompt(char *prompt);

/// @brief			Readline wrapper
/// @param line_buf	Line buffer
/// @note			Used in ft_parser()
void		ft_readline(char ***line_buf)
{
	char	*prompt;

	prompt = ft_get_prompt(MAG"$>"NC);
	// prompt = "$>";
	**line_buf = readline(prompt);
	ft_free(prompt);
	if (!**line_buf)
		**line_buf = ft_strdup("exit");
	add_history(**line_buf);
}

static char	*ft_get_prompt(char *prompt)
{
	char	*pwd;
	char	*ret;
	char	*tmp;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	tmp = NULL;
	tmp = ft_strdup(pwd);
	ft_free(pwd);
	if (tmp)
	{
		ret = ft_strjoin(tmp, prompt);
		ft_free(tmp);
		return (ret);
	}
	else
		return (free(pwd), ft_err(pwd, 0), prompt);
}
