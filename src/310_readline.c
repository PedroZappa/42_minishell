/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   310_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:46:35 by passunca          #+#    #+#             */
/*   Updated: 2024/08/08 12:41:36 by gfragoso         ###   ########.fr       */
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

static char	*ft_get_bash(t_shell *sh, char *prompt);
static char	*ft_bash(t_shell *sh, char *cwd);
static char	*ft_build_bash(t_shell *sh, char *cwd, int i);
static char	*ft_add_user(t_shell *sh, char *prompt, int i);

/// @brief			Readline wrapper
/// @param line_buf	Line buffer
/// @param home		Home directory
/// @note			Used in ft_parser()
void	ft_readline(char **line_buf, t_shell *sh)
{
	char	*prompt;

	prompt = ft_get_bash(sh, BGRN"$> "NC);
	*line_buf = readline(prompt);
	ft_free(prompt);
	if (!*line_buf)
		*line_buf = ft_strdup("exit");
	if (ft_strlen(*line_buf) > 0)
		add_history(*line_buf);
}

/// @brief			Get prompt
/// @param prompt	Prompt string
/// @param home		Home directory
/// @return			Prompt
/// @note			Used in ft_readline()
static char	*ft_get_bash(t_shell *sh, char *prompt)
{
	char	*pwd;
	char	*ret;
	char	*bash;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	bash = ft_bash(sh, pwd);
	if (bash)
	{
		ret = ft_strjoin(bash, prompt);
		return (ft_free(pwd), ft_free(bash), ret);
	}
	else
		return (ft_free(pwd), ft_free(bash), ft_err(pwd, 0), prompt);
}

/// @brief			Build bash prompt
/// @param sh		Pointer to a t_shell struct
/// @param cwd		Pointer to cwd string
/// @return			Bash prompt
/// @note			Used in ft_gwt_prompt()
static char	*ft_bash(t_shell *sh, char *cwd)
{
	char	*tmp;
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	if (!cwd)
		return (ret);
	tmp = ft_build_bash(sh, cwd, i);
	if (!tmp)
		ret = ft_strdup(cwd);
	ret = ft_add_user(sh, tmp, i);
	free(tmp);
	return (ret);
}

/// @brief			Build bash prompt
/// @param cwd		Pointer to cwd string
/// @return			Bash prompt
/// @note			Used in ft_gwt_prompt()
static char	*ft_build_bash(t_shell *sh, char *cwd, int i)
{
	char	*bash;
	int		cwd_len;
	int		home_len;

	cwd_len = ft_strlen(cwd);
	home_len = ft_strlen(sh->home);
	if (strncmp(cwd, sh->home, ft_strlen(sh->home)))
		home_len = 0;
	bash = ft_calloc((cwd_len - home_len + (home_len > 0) + 1), sizeof(char));
	i = -1;
	bash[0] = '~';
	while (++i < (cwd_len - home_len))
		bash[i + (home_len > 0)] = cwd[i + home_len];
	bash[i + (home_len > 0)] = '\0';
	return (bash);
}

/// @brief			Add user and host to prompt
/// @param sh		Pointer to a t_shell struct
/// @param prompt	Prompt string
/// @return			Prompt
/// @note			Used in ft_bash()
static char	*ft_add_user(t_shell *sh, char *prompt, int i)
{
	char	*ret;
	int		user_len;
	int		total_len;
	int		prompt_len;
	int		j;

	user_len = ft_strlen(sh->user);
	prompt_len = ft_strlen(prompt);
	total_len = user_len + 1;
	ret = ft_calloc(total_len + prompt_len + 5, sizeof(char));
	i = -1;
	while (++i < user_len)
		ret[i] = sh->user[i];
	ft_strcpy(ret + i, "@42:");
	i += 4;
	j = -1;
	while (++j < prompt_len)
	{
		ret[i] = prompt[j];
		++i;
	}
	ret[i] = '\0';
	return (ret);
}

/** @} */
