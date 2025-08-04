/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_finalizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:47:26 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/04 17:14:36 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_redirs(t_token **current, t_token **next, t_data *data);
static void	replace_cmds_args(bool *new_pipe, t_token *current);

void	parsing_finalizer(t_data *data)
{
	bool	new_pipe;
	t_token	*current;
	t_token	*next;

	new_pipe = true;
	current = data->lst_tok;
	while (current)
	{
		next = current->next;
		if (current->content[0] == '\0')
			ft_lst_tok_remove(&data->lst_tok, current);
		else if (current->type != TOK_WORD && current->type != TOK_PIPE)
		{
			replace_redirs(&current, &next, data);
			continue ;
		}
		if (current->type == TOK_PIPE)
			new_pipe = true;
		if (current->type == TOK_WORD)
			replace_cmds_args(&new_pipe, current);
		current = next;
	}
}

// Removes redirection symbols and marks the following word as redirection.
static void	replace_redirs(t_token **current, t_token **next, t_data *data)
{
	(*next)->type = (*current)->type;
	ft_lst_tok_remove(&data->lst_tok, *current);
	*current = (*next)->next;
}

// Defines commands and arguments.
static void	replace_cmds_args(bool *new_pipe, t_token *current)
{
	if (*new_pipe == true)
	{
		current->type = TOK_CMD;
		*new_pipe = false;
	}
	else
		current->type = TOK_ARG;
}
