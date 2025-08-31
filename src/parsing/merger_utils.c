/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 11:41:01 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/31 12:00:01 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prep_app(t_exec *node, t_token *current, t_data *data)
{
	size_t	count;
	t_token	*temp;

	count = 0;
	temp = current;
	while (temp && temp->type != TOK_PIPE)
	{
		if (temp->type == TOK_APP)
			count++;
		temp = temp->next;
	}
	node->app = ft_calloc(count + 1, sizeof(char *));
	if (!node->app)
		clean_merge(node, data);
}

void	prep_cmd_arg(t_exec *node, t_token *current, t_data *data)
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

void	prep_in(t_exec *node, t_token *current, t_data *data)
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
	node->in = ft_calloc(count + 1, sizeof(char *));
	if (!node->in)
		clean_merge(node, data);
}

void	prep_out(t_exec *node, t_token *current, t_data *data)
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
	node->out = ft_calloc(count + 1, sizeof(char *));
	if (!node->out)
		clean_merge(node, data);
}
