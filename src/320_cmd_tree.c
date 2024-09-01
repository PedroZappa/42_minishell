/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   221_tk_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfragoso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:01:09 by gfragoso          #+#    #+#             */
/*   Updated: 2024/08/27 11:01:09 by gfragoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

typedef struct s_tree {
	t_tree_node *start;
	t_tree_node *end;
} t_tree;

typedef struct s_tree_node {
	t_token_type	type;
	char			*name;
	size_t			len;
	t_tree_node		*left;
	t_tree_node		*right;
} t_tree_node;

t_tree_node	*ft_tn_new(char *line, t_token_type type, int len)
{
	t_tree_node	*ret;

	ret = ft_calloc(1, sizeof(t_tree_node));
	if (ret == NULL)
		return (ft_err(MALLOC_ERR, errno), NULL);
	ret->name = ft_substr(line, 0, len);
	ret->type = type;
	ret->len = len;
	ret->left = NULL;
	ret->right = NULL;
	return (ret);
}

void	ft_tree_node_destroy(t_tree_node **node)
{
	if (node == NULL || *node == NULL)
		return;
	if ((*node)->name != NULL)
		free((*node)->name);
	free(*node);
	*node = NULL;
}

t_tree	*ft_tree_new()
{
	t_tree *ret;

	ret = ft_calloc(1, sizeof(t_tree));
	if (ret = NULL)
		return (ft_err(MALLOC_ERR, errno), NULL);
	ret->start = ft_tn_new(TK_NULL, NULL, 0);
	if (ret = NULL)
	{
		return (ft_err(MALLOC_ERR, errno), NULL);
	}
	ret->end = ret->start;
	return ret;
}

void	ft_tree_destroy_loop(t_tree_node *node)
{
	if (node == NULL)
		return;
	ft_tree_destroy_loop(node->left);
	ft_tree_destroy_loop(node->right);
	ft_tree_node_destroy(&node);
}

void	ft_tree_destroy(t_tree **tree)
{
	if (tree == NULL || *tree == NULL)
		return;
	ft_tree_destroy_loop((*tree)->start);
	free(tree);
}

void	ft_tree_add(t_tree *tree, t_tree_node *node, t_tk_ops *tk_op)
{
	if (tk_op->type == TK_CMD)
	{
		if (tk_op->tkn)
			ft_free(tk_op->tkn);
		if (tree->end->left == NULL)
			tree->end->left = node;
		else if (tree->end->right == NULL)
			tree->end->right = node;
		
	}
}
