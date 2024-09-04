/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   782_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:05:45 by gfragoso          #+#    #+#             */
/*   Updated: 2024/08/22 01:05:45 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief Get the length of the reduced path
/// @param elems Path elements
/// @return The length of the reduced path
size_t	ft_path_reduced_len(char **elems)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (elems[i])
	{
		j += ft_strlen(elems[i]);
		i++;
	}
	return (i + j + 2);
}

/// @brief Combines the pwd and the path
/// @param pwd The current working directory
/// @param path The path to combine
/// @return The combined path
char	*ft_path_combine(char const *pwd, char const *path)
{
	char	*ret;
	size_t	pwd_len;
	size_t	path_len;

	if (pwd == NULL || path == NULL)
		return (NULL);
	pwd_len = ft_strlen(pwd);
	pwd_len -= pwd[pwd_len - 1] == '/';
	path_len = ft_strlen(path);
	path_len -= path[path_len - 1] == '/';
	ret = malloc(sizeof(char) * (pwd_len + path_len + 2));
	if (ret == NULL)
		return (NULL);
	ft_memcpy(ret, pwd, pwd_len);
	ft_memcpy((ret + pwd_len + 1), path, path_len);
	ret[pwd_len] = '/';
	ret[pwd_len + path_len + 1] = '\0';
	return (ret);
}

/// @brief Home expansion
/// @param sh Pointer to a t_shell struct
/// @param tk Pointer to a t_tk_ops struct
void	ft_home_expand(t_shell *sh, t_tk_ops *tk)
{
	char	*tkn_str;

	tkn_str = ft_strdup(tk->tkn);
	if (tk->tkn[0] == '~' && sh->home)
	{
		ft_free(tk->tkn);
		tk->tkn = ft_strjoin(sh->home, tkn_str + 1);
	}
	ft_free(tkn_str);
}
