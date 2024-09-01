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

int	ft_get_line(t_list *list, char **temp, int *i, char **buf)
{
	char	*ret;

	ret = readline(BWHT"> "NC);
	if (ret == NULL)
	{
		ft_lstclear(&list, free);
		*buf = ft_strdup("exit");
		return (FAILURE);
	}
	ft_lstadd_back(&list, ft_lstnew(ret));
	*temp = ret;
	*i = 0;
	return (SUCCESS);
}

void	ft_vq_loop(t_list *list, char *temp, char **buf)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (temp[i])
	{
		if ((temp[i] == '\'') || (temp[i] == '\"'))
		{
			if (c == temp[i])
				c = 0;
			else if (c == 0)
				c = temp[i];
		}
		i++;
		if (temp[i] == '\0' && c != 0)
			if (ft_get_line(list, &temp, &i, buf) == FAILURE)
				return ;
	}
}

void	ft_verify_quotes(char **buf)
{
	char	*temp;
	t_list	*list;

	list = ft_lstnew(*buf);
	if (list == NULL)
		return ;
	temp = *buf;
	ft_vq_loop(list, temp, buf);
	temp = ft_compress_list(list, '\n');
	ft_lstclear(&list, free);
	*buf = temp;
}

char	*ft_compress_list(t_list *list, char delim)
{
	int		i;
	char	*ret;
	t_list	*temp;

	temp = list;
	if (list == NULL)
		return (NULL);
	i = 0;
	while (temp)
	{
		i += ft_strlen(temp->content);
		temp = temp->next;
	}
	ret = ft_calloc(i + ft_lstsize(list), sizeof(char));
	temp = list;
	i = 0;
	while (temp)
	{
		ft_strcpy(ret + i, temp->content);
		i += ft_strlen(temp->content);
		temp = temp->next;
		if (temp)
			ret[i++] = delim;
	}
	return (ret);
}
