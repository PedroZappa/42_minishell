/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   311_readline_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:25:25 by gfragoso          #+#    #+#             */
/*   Updated: 2024/09/02 00:04:17 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_compress_list(t_list *list, char delim);

char	*ft_compress_free_list(t_list **list, char delim)
{
	char	*ret;

	if (list == NULL)
		return (NULL);
	ret = ft_compress_list(*list, delim);
	ft_lstclear(list, free);
	return (ret);
}

/// @brief			Compress list
/// @param list		Pointer to a t_list struct
/// @param delim	HereDoc Delimiter
/// @return			SUCCESS(Compressed list)
/// @return			FAILURE(NULL)
static char	*ft_compress_list(t_list *list, char delim)
{
	int		i;
	char	*ret;
	t_list	*curr_node;

	curr_node = list;
	i = 0;
	while (curr_node)
	{
		i += ft_strlen(curr_node->content);
		curr_node = curr_node->next;
	}
	ret = ft_calloc(i + ft_lstsize(list) * (delim != '\0')
			+ (delim == '\0'), sizeof(char));
	curr_node = list;
	i = 0;
	while (curr_node)
	{
		ft_strcpy(ret + i, curr_node->content);
		i += ft_strlen(curr_node->content);
		curr_node = curr_node->next;
		if (curr_node && delim != '\0')
			ret[i++] = delim;
	}
	return (ret);
}
