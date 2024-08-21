/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   780_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:41:46 by gfragoso          #+#    #+#             */
/*   Updated: 2024/08/09 11:45:11 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @defgroup 	path Path
* @{
*
* @brief		Check if path exists
* @version		1.0
***/

#include "../inc/minishell.h"

/// @brief			Check if path exists
/// @param sh		Pointer to a t_shell struct
/// @param n		Command index
/// @return			SUCCESS(stat_ret)
int	ft_path(t_shell *sh, int n)
{
	t_stat	sb;
	int		stat_ret;

	memset(&sb, 0, sizeof(t_stat));
	stat_ret = stat(sh->cmds[n].argv[0], &sb);
	if ((sb.st_mode & __S_IFMT) == __S_IFDIR)
		ft_fprintf(STDOUT_FILENO, "bash: %s: Is a directory\n",
			sh->cmds[n].argv[0]);
	if (stat_ret == -1)
		ft_fprintf(STDERR_FILENO, "bash: %s: No such file or directory\n",
			sh->cmds[n].argv[0]);
	return (stat_ret);
}

char	*join_path(char const *s1, char const *s2)
{
	char	*ret;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s1_len -= s1[s1_len - 1] == '/';
	s2_len = ft_strlen(s2);
	s2_len -= s2[s2_len - 1] == '/';
	ret = malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (ret == NULL)
		return (NULL);
	ft_memcpy(ret, s1, s1_len);
	ft_memcpy((ret + s1_len + 1), s2, s2_len);
	ret[s1_len] = '/';
	ret[s1_len + s2_len + 1] = '\0';
	return (ret);
}

char	*diminish_path(char *path)
{
	char	*ret;
	int		i;
	int		j;
	int		k;
	char	**elems;

	elems = ft_split(path, '/');
	i = 0;
	j = 0;
	while (elems[i])
	{
		if (ft_strcmp(elems[i], "..") == 0)
		{
			j -= j > 0;
		}
		else if (ft_strcmp(elems[i], "."))
		{
			elems[j] = elems[i];
			j++;
		}
		i++;
	}
	elems[j] = '\0';
	if (j == 0)
		return (strdup("/"));
	j = 0;
	i = 0;
	while (elems[i])
	{
		j += ft_strlen(elems[i]);
		i++;
	}
	ret = malloc(j + i + 2);
	k = 0;
	i = 0;
	while (elems[i])
	{
		j = 0;
		ret[k] = '/';
		k++;
		while (elems[i][j])
		{
			ret[k] = elems[i][j];
			j++;
			k++;
		}
		i++;
	}
	ret[k] = '\0';
	i = 0;
	return (ret);
}

char	*ft_resolve_path(char *pwd, char *path)
{
	char	*ret;
	char	*temp;

	ret = NULL;
	if (path == NULL || pwd == NULL)
		return (pwd);
	if (path[0] == '/'
		|| (path[0] == '~' && (path[1] == '\0' || path[1] == '/')))
		temp = ft_strdup(path);
	else
		temp = join_path(pwd, path);
	if (temp == NULL)
		return (pwd);
	ret = diminish_path(temp);
	return (ret);
}
/** @} */
