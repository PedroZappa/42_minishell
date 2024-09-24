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

static char	*ft_build_cwd(char *cwd, char *home);
static int	ft_verify_quotes(char **line_buf);
static char	*ft_build_prompt(t_shell *sh);
static char	*ft_prompt_user(t_shell *sh);

/// @brief			Readline wrapper
/// @param line_buf	Line buffer
/// @param home		Home directory
/// @note			Used in ft_parser()
/// @return			SUCCESS(0)
///					FAILURE(!=0)	
int	ft_readline(char **line_buf, t_shell *sh)
{
	char	*prompt;
	int		exit;

	prompt = ft_build_prompt(sh);
	*line_buf = readline(prompt);
	ft_free(prompt);
	if (*line_buf == NULL)
		*line_buf = ft_strdup("exit");
	exit = ft_verify_quotes(line_buf);
	if (exit)
		return (exit);
	if (ft_strlen(*line_buf) > 0)
		add_history(*line_buf);
	return (SUCCESS);
}

/// @brief				Verify quotes
/// @param line_buf		Line buffer
/// @return				SUCCESS(0)
///						FAILURE(!=0)
static int	ft_verify_quotes(char **line_buf)
{
	int		i;
	char	q_type;
	char	*temp;

	i = 0;
	q_type = 0;
	temp = *line_buf;
	while (temp[i])
	{
		if ((temp[i] == '\'') || (temp[i] == '\"'))
		{
			if (q_type == temp[i])
				q_type = 0;
			else if (q_type == 0)
				q_type = temp[i];
		}
		i++;
	}
	if (q_type != 0)
		return (ft_syntax_char_err(q_type));
	return (SUCCESS);
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
	char	*home;

	temp = ft_prompt_user(sh);
	cwd = ft_get_var("PWD", sh->envp);
	if (cwd == NULL)
		cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		home = ft_get_var("HOME", sh->envp);
		if (home == NULL)
			home = ft_strdup(sh->home);
		pwd = ft_build_cwd(cwd, home);
		if (pwd)
			temp = ft_strjoin_free(temp, pwd);
		ft_free(cwd);
		ft_free(home);
	}
	ret = ft_strjoin(temp, "$ ");
	return (ft_free(temp), ret);
}

/// @brief			Formats the Current Working Directory (cwd) 
/// 						to omit the home path and replace it by '~'
/// @param cwd		String containing the path to the cwd
///	@param home		Home path
/// @return			Formatted cwd
/// @note			Used in ft_build_prompt()
static char	*ft_build_cwd(char *cwd, char *home)
{
	char	*ret;
	int		i;
	int		cwd_len;
	int		home_len;

	cwd_len = ft_strlen(cwd);
	home_len = ft_strlen(home);
	if (ft_strncmp(cwd, home, home_len) != 0)
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
/// @return			SUCCESS(Bash prompt)
/// @note			Used in ft_readline()
static char	*ft_prompt_user(t_shell *sh)
{
	char	*ret;
	char	*temp;

	ret = ft_strjoin(sh->user, "@");
	temp = ft_strjoin(ret, sh->hostname);
	ft_free(ret);
	ret = ft_strjoin(temp, ":");
	ft_free(temp);
	return (ret);
}

/** @} */
