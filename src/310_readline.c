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

static char	*ft_get_prompt(t_shell ***sh, char *prompt);
static char	*ft_trim_cwd(t_shell ****sh, char *cwd);
static char	*ft_build_cwd(t_shell *****sh, char **cwd);
static char	*ft_add_user_host(t_shell *****sh, char *prompt);

/// @brief			Readline wrapper
/// @param line_buf	Line buffer
/// @param home		Home directory
/// @note			Used in ft_parser()
void		ft_readline(char ***line_buf, t_shell **sh)
{
	char	*prompt;

	prompt = ft_get_prompt(&sh, MAG"$> "NC);
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
static char	*ft_get_prompt(t_shell ***sh, char *prompt)
{
	char	*pwd;
	char	*ret;
	char	*trim;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	trim = ft_trim_cwd(&sh, pwd);
	if (trim)
	{
		ret = ft_strjoin(trim, prompt);
		return (ft_free(pwd), ft_free(trim), ret);
	}
	else
		return (free(pwd), free(trim), ft_err(pwd, 0), prompt);
}

static char	*ft_trim_cwd(t_shell ****sh, char *cwd)
{
	char	*tmp;
	char	*ret;

	ret = NULL;
	if (!cwd)
		return (ret);
	tmp = ft_build_cwd(&sh, &cwd);
	// ret = ft_build_cwd(&sh, &cwd);
	if (!tmp)
		ret = ft_strdup(cwd);
	ret = ft_add_user_host(&sh, tmp);
	free(tmp);
	return (ret);
}

static char	*ft_build_cwd(t_shell *****sh, char **cwd)
{
	char	*ret;
	char	*trim;
	int		cwd_len;
	int		home_len;
	int		i;
	
	trim = *cwd;
	cwd_len = ft_strlen(*cwd); 
	home_len = ft_strlen((****sh)->home);
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

static char	*ft_add_user_host(t_shell *****sh, char *prompt)
{
	char	*ret;
	int		user_len;
	// int		host_len;
	int		total_len;
	int		prompt_len;
	int		i;
	int		j;

	user_len = ft_strlen((****sh)->user);
	// host_len = ft_strlen((****sh)->host);
	prompt_len = ft_strlen(prompt);
	total_len = user_len + 1;
	ret = malloc(sizeof(char) * (total_len + prompt_len + 2));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < user_len)
		ret[i] = (****sh)->user[i];
    ret[i++] = '@';
    ret[i++] = ':';
    for (j = 0; j < prompt_len; j++, i++)
        ret[i] = prompt[j];
    ret[i] = '\0';
	return (ret);
}

/** @} */
