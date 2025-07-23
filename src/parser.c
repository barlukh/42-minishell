/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:59:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/23 14:09:03 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_quotes(char *content, char *quote);
static void	expand_vars(char *content, char quote, t_env **lst_env);

int	parser(t_env **lst_env, t_token **lst_tok)
{
	char	quote;
	t_token	*current;

	quote = '\0';
	current = *lst_tok;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			if (check_quotes(current->content, &quote) != SUCCESS)
				return (FAILURE);
			expand_vars(current->content, quote, lst_env);
		}
		current = current->next;
	}
	return (SUCCESS);
}

// Checks for syntax errors with unclosed quotes.
static int	check_quotes(char *content, char *quote)
{
	size_t	quote_count;

	if (*content == '"')
		*quote = *content;
	else if (*content == '\'')
		*quote = *content;
	else
		return (SUCCESS);
	quote_count = 0;
	while (*content)
	{
		if (*content == '"' && *quote == '"')
			quote_count++;
		else if (*content == '\'' && *quote == '\'')
			quote_count++;
		content++;
	}
	if (quote_count % 2 != 0)
		return (FAILURE);
	return (SUCCESS);
}

// Expands environment variables.
static void	expand_vars(char *content, char quote, t_env **lst_env)
{
	while (*content)
	{
		if (*content == '$' && quote != '\'')
		{
			j = 0;
			while (env[j])
		}
			
	}
}
