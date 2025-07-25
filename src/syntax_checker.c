/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:59:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/25 13:23:08 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	has_valid_quotes(char *content);
static bool	has_valid_pipes(t_token *current, t_token **lst_tok);
static bool	has_valid_redirs(t_token *current);

bool	syntax_checker(t_token **lst_tok)
{
	t_token	*current;

	current = *lst_tok;
	while (current)
	{
		if (current->type == TOK_WORD
			&& has_valid_quotes(current->content) != true)
			return (FAILURE);
		else if (current->type == TOK_PIPE
			&& has_valid_pipes(current, lst_tok) != true)
			return (FAILURE);
		else if (current->type != TOK_WORD && current->type != TOK_PIPE
			&& has_valid_redirs(current) != true)
			return (FAILURE);
		current = current->next;
	}
	return (SUCCESS);
}

// Checks for invalid quotes.
static bool	has_valid_quotes(char *content)
{
	char	quote;
	size_t	count;

	quote = '\0';
	count = 0;
	while (*content)
	{
		if (quote == '\0' && ft_isquote(*content))
		{
			quote = *content;
			count++;
		}
		else if (*content == quote)
			count++;
		content++;
	}
	if (count % 2 != 0)
		return (false);
	return (true);
}

// Checks for invalid pipes.
static bool	has_valid_pipes(t_token *current, t_token **lst_tok)
{
	if (current == *lst_tok)
		return (false);
	if (current->next == NULL)
		return (false);
	if (current->next->type == TOK_PIPE)
		return (false);
	return (true);
}

// Checks for invalid redirections.
static bool	has_valid_redirs(t_token *current)
{
	if (current->next == NULL)
		return (false);
	if (current->next->type != TOK_WORD)
		return (false);
	return (true);
}
