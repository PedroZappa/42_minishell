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

static char	*ft_build_cwd(t_shell *sh, char *cwd);
static char	*ft_build_prompt(t_shell *sh);
static char	*ft_prompt_user(t_shell *sh);

/// @brief			Readline wrapper
/// @param line_buf	Line buffer
/// @param home		Home directory
/// @note			Used in ft_parser()
void	ft_readline(char **line_buf, t_shell *sh)
{
	char	*prompt;

	prompt = ft_build_prompt(sh);
	*line_buf = readline(prompt);
	ft_free(prompt);
	if (*line_buf == NULL)
		*line_buf = ft_strdup("exit");
	if (ft_strlen(*line_buf) > 0)
		add_history(*line_buf);
}

/// @brief			Formats the Current Working Directory (cwd) 
/// 						to omit the home path and replace it by '~'
/// @param sh		Pointer to a t_shell struct
/// @param cwd	String containing the path to the cwd
/// @return			Formatted cwd
/// @note			Used in ft_build_prompt()
static char	*ft_build_cwd(t_shell *sh, char *cwd)
{
	char	*ret;
	int		i;
	int		cwd_len;
	int		home_len;

	cwd_len = ft_strlen(cwd);
	home_len = ft_strlen(sh->home);
	if (ft_strncmp(cwd, sh->home, home_len) != 0)
		home_len = 0;
	ret = ft_calloc((cwd_len - home_len + (home_len > 0) + 1), sizeof(char));
	i = 0;
	ret[0] = '~';
	while (i < (cwd_len - home_len))
	{
		ret[i + (home_len > 0)] = cwd[i + home_len];
		i++;
	}
	ret[i + (home_len > 0)] = '\0';
	return (ret);
}

/// @brief			Build bash prompt
/// @param sh		Pointer to a t_shell struct
/// @return			Bash prompt
/// @note			Used in ft_readline()
static char	*ft_build_prompt(t_shell *sh)
{
	char	*ret;
	char	*temp;
	char	*cwd;
	char	*pwd;

	temp = ft_prompt_user(sh);
	cwd = ft_get_var("PWD", sh->envp, NULL);
	if (cwd != NULL)
	{
		pwd = ft_build_cwd(sh, cwd);
		if (pwd)
			temp = ft_strjoin_free(temp, pwd);
		ft_free(cwd);
	}
	ret = ft_strjoin(temp, BWHT"$ "NC);
	return (ft_free(temp), ret);
}

static char	*ft_prompt_user(t_shell *sh)
{
	char	*ret;
	char	*temp;

	temp = ft_strjoin(RED, sh->user);
	ret = ft_strjoin(temp, "@");
	ft_free(temp);
	temp = ft_strjoin(ret, sh->hostname);
	ft_free(ret);
	ret = ft_strjoin(temp, BWHT":"BBLU);
	ft_free(temp);
	return (ret);
}

/** @} */
