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
static char	*ft_trim_cwd(char *cwd);


/// @brief			Readline wrapper
/// @param line_buf	Line buffer
/// @note			Used in ft_parser()
void		ft_readline(char ***line_buf)
{
	char	*prompt;

	prompt = ft_get_prompt(MAG"$>"NC);
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
	char	*trim;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	tmp = ft_strdup(pwd);
	ft_free(pwd);
	trim = ft_trim_cwd(tmp);
	ft_free(tmp);
	if (trim)
	{
		ret = ft_strjoin(trim, prompt);
		ft_free(trim);
		return (ret);
	}
	else
		return (free(pwd), free(trim), ft_err(pwd, 0), prompt);
}

static char	*ft_trim_cwd(char *cwd)
{
	// char	*ret;
	char	*tmp;
	int		len;
	// int		i;

	len = (ft_strlen(cwd) - 1);
	while (cwd[len] && (cwd[len] != '/'))
		--len;
	tmp = ft_substr(cwd, len, (ft_strlen(cwd) - len));
	// len = ft_strlen(tmp);
	// ret = malloc(2 * (len + 1));
	// if (!ret)
	// 	return (NULL);
	// ret[0] = '.';
	// ret[1] = '.';
	// i = 0;
	// while (i < len)
	// {
	// 	ret[i + 2] = tmp[i];
	// 	++i;
	// }
	// ret[i + 2] = '\0';
	// if (tmp)
	// 	ft_free(tmp);
	return (tmp);
}
