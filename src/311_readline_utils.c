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

int	ft_get_line(t_list *list, char **temp, int *i, char **line_buf);

/// @brief				Readline heredoc loop: Prompt user for input if
///						unclosed quotes are parsed
/// @param list			Pointer to a t_list struct containing lines read
/// @param temp			Reference to the line read
/// @param line_buf		
void	ft_vq_loop(t_list *list, char *temp, char **line_buf)
{
	int		i;
	char	q_type;

	i = 0;
	q_type = 0;
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
		if (temp[i] == '\0' && q_type != 0)
			if (ft_get_line(list, &temp, &i, line_buf) == FAILURE)
				return ;
	}
}

///
/// @brief				Get a line
/// @param list			Pointer to a t_list struct
/// @param temp			Reference to save the read line
/// @param i			Reference to current line index
/// @param line_buf		
/// @return			SUCCESS(0)
/// @return			FAILURE(1)
int	ft_get_line(t_list *list, char **temp, int *i, char **line_buf)
{
	char	*ret;

	ret = readline(BWHT"> "NC);
	if (ret == NULL)
	{
		ft_lstclear(&list, free);
		*line_buf = ft_strdup("exit");
		return (FAILURE);
	}
	ft_lstadd_back(&list, ft_lstnew(ret));
	*temp = ret;
	*i = 0;
	return (SUCCESS);
}

/// @brief			Compress list
/// @param list		Pointer to a t_list struct
/// @param delim	HereDoc Delimiter
/// @return			SUCCESS(Compressed list)
/// @return			FAILURE(NULL)
char	*ft_compress_list(t_list *list, char delim)
{
	int		i;
	char	*ret;
	t_list	*curr_node;

	curr_node = list;
	if (list == NULL)
		return (NULL);
	i = 0;
	while (curr_node)
	{
		i += ft_strlen(curr_node->content);
		curr_node = curr_node->next;
	}
	ret = ft_calloc(i + ft_lstsize(list), sizeof(char));
	curr_node = list;
	i = 0;
	while (curr_node)
	{
		ft_strcpy(ret + i, curr_node->content);
		i += ft_strlen(curr_node->content);
		curr_node = curr_node->next;
		if (curr_node)
			ret[i++] = delim;
	}
	return (ret);
}
