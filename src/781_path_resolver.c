/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   781_path_resolver.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:03:31 by gfragoso          #+#    #+#             */
/*   Updated: 2024/08/22 01:03:31 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_path_arr_to_str(char **elems)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	ret = ft_calloc(ft_path_reduced_len(elems), sizeof(char));
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
	return (ret);
}

int	ft_path_elems_final_size(char **elems)
{
	int		i;
	int		j;

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
			j++;
		}
		i++;
	}
	return (j);
}

char	**ft_path_arr_reduce(char **elems, size_t final_size)
{
	char	**ret;
	int		i;
	int		j;

	ret = ft_calloc(final_size + 1, sizeof(char *));
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
			ret[j] = elems[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*ft_path_resolve_inner(char *path)
{
	char		*ret;
	char		**elems;
	char		**final_elems;
	size_t		final_size;

	elems = ft_split(path, '/');
	final_size = ft_path_elems_final_size(elems);
	final_elems = ft_path_arr_reduce(elems, final_size);
	if (final_size == 0)
		return ((void)ft_free_arr(elems), strdup("/"));
	ret = ft_path_arr_to_str(final_elems);
	return (free(final_elems), (void)ft_free_arr(elems), ret);
}

char	*ft_path_resolve(char *pwd, char *path)
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
		temp = ft_path_combine(pwd, path);
	if (temp == NULL)
		return (pwd);
	ret = ft_path_resolve_inner(temp);
	return (ft_free(temp), ret);
}
