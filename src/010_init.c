/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   010_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:53:41 by passunca          #+#    #+#             */
/*   Updated: 2024/08/08 12:10:37 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @defgroup init Init
* @{
*
* @brief		Initialize minishell
* @version		1.0
***/

#include "../inc/minishell.h"

static void	ft_shlvl(t_shell *sh);

/// @brief		Initialize minishell
/// @param sh	Pointer to a t_shell struct
/// @param envp	Pointer to environment variables
/// @return		SUCCESS(0)
///				FAILURE(1)
/// @note		Used in main()
int	ft_init(t_shell *sh, char **envp)
{
	sh->envp = ft_init_env(envp);
	ft_shlvl(sh);
	if (sh->envp == NULL)
		return (ft_err(ENV_INIT_ERR, errno), FAILURE);
	sh->home = ft_get_var("HOME", sh->envp);
	sh->user = ft_get_var("USER", sh->envp);
	sh->hostname = ft_get_hostname();
	ft_set_var("OLDPWD", NULL, &sh->envp);
	ft_get_termios(STDIN_FILENO, &sh->termios);
	sh->n_pipes = 0;
	return (SUCCESS);
}

/// @brief		Initialize shell level
/// @param sh	Pointer to a t_shell struct
/// @note		Used in main()
static void	ft_shlvl(t_shell *sh)
{
	static int	lvl;
	char		*shlvl;
	char		*new;
	int			i;

	lvl = 0;
	shlvl = ft_get_var("SHLVL", sh->envp);
	if (shlvl)
	{
		if (lvl == 0)
		{
			lvl = 1;
			i = ft_atoi(shlvl);
		}
		else
			i = (ft_atoi(shlvl) + 1);
		new = ft_itoa(i);
		if (new == NULL)
			ft_err(MALLOC_ERR, errno);
		ft_set_var("SHLVL", new, &sh->envp);
		free(new);
		free(shlvl);
	}
	else
		ft_set_var("SHLVL", "1", &sh->envp);
}

/// @brief		Normalize hostname string
///				Removes \n and everything after a '.'
/// @return		SUCCESS(hostname)
/// @note		Used in ft_init()
char	*ft_hostname_norm(char *hostname)
{
	size_t	len;
	char	*dot;

	len = ft_strlen(hostname);
	if (hostname[len - 1] == '\n')
		hostname[len - 1] = '\0';
	dot = ft_strchr(hostname, '.');
	if (dot != NULL)
		*dot = '\0';
	return (hostname);
}

/// @brief		Get hostname
/// @return		SUCCESS(hostname)
/// @note		Used in ft_init()
char	*ft_get_hostname(void)
{
	int		fd;
	char	*ret;
	char	*temp;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd != -1)
	{
		ret = get_next_line(fd);
		temp = get_next_line(fd);
		while (temp)
		{
			ft_free(temp);
			temp = get_next_line(fd);
		}
		if (ret == NULL || ret[0] == '\0')
			return (close(fd), ft_strdup("42"));
		ret = ft_hostname_norm(ret);
	}
	else
		ret = ft_strdup("42");
	close(fd);
	return (ret);
}
/** @} */
