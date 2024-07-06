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
static char	*ft_trim_cwd(char *cwd, char *home);
static char	*ft_build_cwd(char **cwd, char *home);

/// @brief			Readline wrapper
/// @param line_buf	Line buffer
/// @param home		Home directory
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

/// @brief			Get prompt
/// @param prompt	Prompt string
/// @param home		Home directory
/// @return			Prompt
/// @note			Used in ft_readline()
static char	*ft_get_prompt(char *prompt, char **home)
{
	char	*pwd;
	char	*ret;
	char	*trim;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	trim = ft_trim_cwd(pwd, *home);
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

static char	*ft_trim_cwd(char *cwd, char *home)
{
	char	*ret;

	(void)home;
	ret = NULL;
	if (!cwd)
		return (ret);
	ret = ft_build_cwd(&cwd, home);
	if (!ret)
		ret = ft_strdup(cwd);
	return (ret);
}

static char	*ft_build_cwd(char **cwd, char *home)
{
	char	*ret;
	char	*trim;
	int		cwd_len;
	int		home_len;
	int		i;
	
	trim = *cwd;
	cwd_len = ft_strlen(*cwd);
	home_len = ft_strlen(home);
	ret = malloc(sizeof(char) * ((cwd_len - home_len) + 3));
	if (!ret)
		return (NULL);
	ret[0] = '~';
	i = -1;
	while (++i < cwd_len - home_len)
		ret[i + 1] = trim[home_len + i];
	ret[i + 1] = '\0';
	return (ret);
}

/** @} */
