/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:42:25 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/18 17:43:29 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_ambiguous_exp(t_token *current);

bool	ambiguous_redir(t_data *data)
{
	t_token	*current;

	current = data->lst_tok;
	while (current)
	{
		if (current->type == TOK_IN || current->type == TOK_OUT
			|| current->type == TOK_APP)
		{
			if (current->next)
			{
				if (is_ambiguous_exp(current->next))
				{
					ft_putendl_fd(ERR_MSG_AMB, STDERR_FILENO);
					return (true);
				}
			}
		}
		current = current->next;
	}
	return (false);
}

// Looks for a space, tab, or newline in a selected token.
static bool	is_ambiguous_exp(t_token *current)
{
	char	quote;
	size_t	i;

	quote = '\0';
	i = 0;
	while (current->content[i])
	{
		if (quote == '\0' && ft_isquote(current->content[i]))
			quote = current->content[i];
		else if (current->content[i] == quote)
			quote = '\0';
		else if (quote == '\0' && ft_isifs(current->content[i]))
			return (true);
		i++;
	}
	return (false);
}
