/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   310_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:46:35 by passunca          #+#    #+#             */
/*   Updated: 2024/07/04 10:35:31 by passunca         ###   ########.fr       */
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

static char	*ft_get_prompt(char *prompt, char **home);
static char	*ft_trim_cwd(char *cwd);


/// @brief			Readline wrapper
/// @param line_buf	Line buffer
/// @note			Used in ft_parser()
void		ft_readline(char ***line_buf, char *home)
{
	char	*prompt;

	prompt = ft_get_prompt(MAG"$> "NC, &home);
	**line_buf = readline(prompt);
	ft_free(prompt);
	if (!**line_buf)
		**line_buf = ft_strdup("exit");
	add_history(**line_buf);
}

static char	*ft_get_prompt(char *prompt, char **home)
{
	char	*pwd;
	char	*ret;
	char	*trim;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	trim = ft_trim_cwd(pwd);
	if (trim)
	{
		if (ft_strncmp(pwd, *home, ft_strlen(pwd)) == SUCCESS)
		{
			trim[0] = '~';
			trim[1] = '\0';
		}
		ret = ft_strjoin(trim, prompt);
		return (ft_free(pwd), ft_free(trim), ret);
	}
	else
		return (free(pwd), free(trim), ft_err(pwd, 0), prompt);
}

static char	*ft_trim_cwd(char *cwd)
{
	char	*ret;
	char	*tmp;
	int		len;
	int		i;

	len = (ft_strlen(cwd) - 1);
	while (cwd[len] && (cwd[len] != '/'))
		--len;
	tmp = ft_substr(cwd, len, (ft_strlen(cwd) - len));
	len = ft_strlen(tmp);
	ret = malloc(2 * (len + 1));
	if (!ret)
		return (NULL);
	ret[0] = '.';
	ret[1] = '.';
	i = -1;
	while (++i < len)
		ret[i + 2] = tmp[i];
	ret[i + 2] = '\0';
	if (tmp)
		ft_free(tmp);
	return (ret);
}

/** @} */
