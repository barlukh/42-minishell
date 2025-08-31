/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 08:51:55 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/31 12:05:51 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*merge_main(t_exec *node, t_token *current, t_data *data);
static void		null_terminate_arrays(t_exec *node, size_t *i);

void	merger(t_data *data)
{
	t_exec	*node;
	t_token	*current;

	current = data->lst_tok;
	while (current)
	{
		node = ft_lst_exec_new(NULL, NULL, NULL, NULL);
		if (!node)
			error_general_mem(data);
		prep_app(node, current, data);
		prep_cmd_arg(node, current, data);
		prep_in(node, current, data);
		prep_out(node, current, data);
		data->tok_count++;
		current = merge_main(node, current, data);
		ft_lst_exec_add_back(&data->lst_exec, node);
		if (current && current->type == TOK_PIPE)
			current = current->next;
	}
	ft_lst_tok_clear(&data->lst_tok);
	data->lst_tok = NULL;
}

// Main loop for token merge.
static t_token	*merge_main(t_exec *node, t_token *current, t_data *data)
{
	char	*copy;
	size_t	i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	while (current && current->type != TOK_PIPE)
	{
		copy = ft_strdup(current->content);
		if (!copy)
			clean_merge(node, data);
		if (current->type == TOK_CMD || current->type == TOK_ARG)
			node->cmd_arg[i[0]++] = copy;
		else if (current->type == TOK_IN || current->type == TOK_HERE)
			node->in[i[1]++] = copy;
		else if (current->type == TOK_OUT || current->type == TOK_APP)
			node->out[i[2]++] = copy;
		if (current->type == TOK_APP)
			node->app[i[3]++] = copy;
		current = current->next;
	}
	null_terminate_arrays(node, i);
	return (current);
}

// Null-terminates all arrays in the new token node.
static void	null_terminate_arrays(t_exec *node, size_t *i)
{
	node->cmd_arg[i[0]] = NULL;
	node->in[i[1]] = NULL;
	node->out[i[2]] = NULL;
	node->app[i[3]] = NULL;
}
