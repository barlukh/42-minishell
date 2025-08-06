/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_identifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:36:04 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/05 19:10:33 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_quotes(bool *quote_found, t_token *current);

void	heredoc_identifier(t_data *data)
{
	bool	quote_found;
	t_token	*current;

	current = data->lst_tok;
	while (current)
	{
		quote_found = false;
		if (current->type == TOK_HERE)
		{
			find_quotes(&quote_found, current);
			if (quote_found == true)
				current->next->type = TOK_HERE_QTD;
			else
				current->next->type = TOK_HERE_UNQTD;
		}
		current = current->next;
	}
}

// Looks for quotes withing heredoc delimiters.
static void	find_quotes(bool *quote_found, t_token *current)
{
	size_t	i;

	i = 0;
	while (current->next->content[i])
	{
		if (ft_isquote(current->next->content[i]))
		{
			*quote_found = true;
			return ;
		}
		i++;
	}
}
