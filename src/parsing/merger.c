/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 08:51:55 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/15 15:19:12 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*merge_main(t_exec *node, t_token *current, t_data *data);
static void		prep_cmd_arg(t_exec *node, t_token *current, t_data *data);
static void		prep_red_in(t_exec *node, t_token *current, t_data *data);
static void		prep_red_out(t_exec *node, t_token *current, t_data *data);

void	merger(t_data *data)
{
	t_exec	*node;
	t_token	*current;

	current = data->lst_tok;
	while (current)
	{
		node = ft_lst_exec_new(NULL, NULL, NULL);
		if (!node)
			error_general_mem(data);
		prep_cmd_arg(node, current, data);
		prep_red_in(node, current, data);
		prep_red_out(node, current, data);
		current = merge_main(node, current, data);
		ft_lst_exec_add_back(&data->lst_exec, node);
		if (current && current->type == TOK_PIPE)
			current = current->next;
	}
	ft_lst_tok_clear(&data->lst_tok);
}

// Main loop for token merge.
static t_token	*merge_main(t_exec *node, t_token *current, t_data *data)
{
	char	*copy;
	size_t	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (current && current->type != TOK_PIPE)
	{
		copy = ft_strdup(current->content);
		if (!copy)
			clean_merge(node, data);
		if (current->type == TOK_CMD || current->type == TOK_ARG)
			node->cmd_arg[i[0]++] = copy;
		else if (current->type == TOK_IN || current->type == TOK_HERE)
			node->red_in[i[1]++] = copy;
		else if (current->type == TOK_OUT || current->type == TOK_APP)
			node->red_out[i[2]++] = copy;
		current = current->next;
	}
	node->cmd_arg[i[0]] = NULL;
	node->red_in[i[1]] = NULL;
	node->red_out[i[2]] = NULL;
	return (current);
}

// Allocates memory for an array of commands and arguments.
static void	prep_cmd_arg(t_exec *node, t_token *current, t_data *data)
{
	size_t	count;
	t_token	*temp;

	count = 0;
	temp = current;
	while (temp && temp->type != TOK_PIPE)
	{
		if (temp->type == TOK_CMD || temp->type == TOK_ARG)
			count++;
		temp = temp->next;
	}
	node->cmd_arg = ft_calloc(count + 1, sizeof(char *));
	if (!node->cmd_arg)
		clean_merge(node, data);
}

// Allocates memory for an array of redirections in.
static void	prep_red_in(t_exec *node, t_token *current, t_data *data)
{
	size_t	count;
	t_token	*temp;

	count = 0;
	temp = current;
	while (temp && temp->type != TOK_PIPE)
	{
		if (temp->type == TOK_IN || temp->type == TOK_HERE)
			count++;
		temp = temp->next;
	}
	node->red_in = ft_calloc(count + 1, sizeof(char *));
	if (!node->red_in)
		clean_merge(node, data);
}

// Allocates memory for an array of redirections out.
static void	prep_red_out(t_exec *node, t_token *current, t_data *data)
{
	size_t	count;
	t_token	*temp;

	count = 0;
	temp = current;
	while (temp && temp->type != TOK_PIPE)
	{
		if (temp->type == TOK_OUT || temp->type == TOK_APP)
			count++;
		temp = temp->next;
	}
	node->red_out = ft_calloc(count + 1, sizeof(char *));
	if (!node->red_out)
		clean_merge(node, data);
}
