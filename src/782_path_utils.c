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

char	*ft_path_combine(char const *s1, char const *s2)
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
