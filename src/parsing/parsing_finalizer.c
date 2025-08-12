/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_finalizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:47:26 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/11 18:30:02 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_redirs(t_token **current, t_token **next, t_data *data);
static void	update_pipe(bool *new_pipe, t_token *current);
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
		if (current->type == TOK_HERE)
		{
			ft_lst_tok_remove(&data->lst_tok, current);
			current = next;
			continue ;
		}
		if (current->type == TOK_IN || current->type == TOK_OUT
			|| current->type == TOK_APP)
		{
			replace_redirs(&current, &next, data);
			continue ;
		}
		update_pipe(&new_pipe, current);
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

// Updates the bool flag of a new_pipe.
static void	update_pipe(bool *new_pipe, t_token *current)
{
	if (current->type == TOK_PIPE)
		*new_pipe = true;
}

// Defines commands and arguments.
static void	replace_cmds_args(bool *new_pipe, t_token *current)
{
	if (current->type == TOK_WORD)
	{
		if (*new_pipe == true)
		{
			current->type = TOK_CMD;
			*new_pipe = false;
		}
		else
			current->type = TOK_ARG;
	}
}
