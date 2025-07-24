/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:59:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/24 13:38:47 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	validate_quotes(char *content);
static int	validate_inv_pipes(t_token *current, t_token **lst_tok);
static int	validate_redirs(t_token *current);

int	syntax_checker(t_token **lst_tok)
{
	t_token	*current;

	current = *lst_tok;
	while (current)
	{
		if (current->type == TOK_WORD
			&& validate_quotes(current->content) != SUCCESS)
			return (FAILURE);
		else if (current->type == TOK_PIPE
			&& validate_inv_pipes(current, lst_tok) != SUCCESS)
			return (FAILURE);
		else if (current->type != TOK_WORD && current->type != TOK_PIPE
			&& validate_redirs(current) != SUCCESS)
			return (FAILURE);
		current = current->next;
	}
	return (SUCCESS);
}

// Checks for invalid quotes (unclosed).
static int	validate_quotes(char *content)
{
	char	quote;
	size_t	count;

	quote = '\0';
	count = 0;
	while (*content)
	{
		if (quote == '\0' && (*content == '\'' || *content == '"'))
		{
			quote = *content;
			count++;
		}
		else if (*content == quote)
			count++;
		content++;
	}
	if (count % 2 != 0)
		return (FAILURE);
	return (SUCCESS);
}

// Checks for invalid pipes.
static int	validate_inv_pipes(t_token *current, t_token **lst_tok)
{
	if (current == *lst_tok)
		return (FAILURE);
	else if (current->next == NULL)
		return (FAILURE);
	else if (current->next->type == TOK_PIPE)
		return (FAILURE);
	return (SUCCESS);
}

// Checks for invalid redirections.
static int	validate_redirs(t_token *current)
{
	if (current->next == NULL)
		return (FAILURE);
	else if (current->next->type != TOK_WORD)
		return (FAILURE);
	return (SUCCESS);
}
