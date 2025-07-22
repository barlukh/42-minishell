/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:59:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/22 15:44:19 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	check_quotes(t_token **lst_tok, char *content, char *quote);
// static void	expand_vars(t_token **lst_tok, char *content, char **env, char quote);

void	parser(t_token **lst_tok, t_env **env)
{
	char	quote;
	t_token	*current;

	(void)env;
	quote = '\0';
	current = *lst_tok;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			check_quotes(lst_tok, current->content, &quote);
			// expand_vars(lst_tok, current->content, env, quote);
		}
		current = current->next;
	}
}

// Checks for syntax errors with unclosed quotes.
static void	check_quotes(t_token **lst_tok, char *content, char *quote)
{
	size_t	quote_count;
	size_t	i;

	if (content[0] == '"')
		*quote = content[0];
	else if (content[0] == '\'')
		*quote = content[0];
	else
		return ;
	quote_count = 0;
	i = 0;
	while (content[i])
	{
		if (*quote == '"' && content[i] == '"')
			quote_count++;
		else if (*quote == '\'' && content[i] == '\'')
			quote_count++;
		i++;
	}
	if (quote_count % 2 != 0)
		exit(error_parser(lst_tok));
}

// Expands environment variables.
// static void	expand_vars(t_token **lst, char *content, char **env, char quote)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	while (content[i])
// 	{
// 		if (content[i] == '$' && quote != '\'')
// 		{
// 			j = 0;
// 			while (env[j])
// 		}
			
// 	}
// }
