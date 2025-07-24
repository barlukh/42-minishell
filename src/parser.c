/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:59:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/23 18:47:04 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	validate_quotes(char *content);

int	parser(t_env **lst_env, t_token **lst_tok)
{
	t_token	*current;

	(void)lst_env;
	current = *lst_tok;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			if (validate_quotes(current->content) != SUCCESS)
				return (FAILURE);
		}
		current = current->next;
	}
	return (SUCCESS);
}

// Checks for syntax errors with unclosed quotes.
static int	validate_quotes(char *content)
{
	char	quote;
	size_t	count;

	if (*content != '\'' && *content != '"')
		return (SUCCESS);
	quote = *content;
	count = 0;
	while (*content)
	{
		if (*content == quote)
			count++;
		content++;
	}
	if (count % 2 != 0)
		return (FAILURE);
	return (SUCCESS);
}
