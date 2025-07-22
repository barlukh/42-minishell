/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:59:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/22 09:24:15 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	check_unclosed_quotes(t_token **lst, char *content);

void	parser(t_token **lst)
{
	t_token	*current;

	current = *lst;
	while (current)
	{
		if (current->type == TOKEN_WORD)
			check_unclosed_quotes(lst, current->content);
		current = current->next;
	}
}

static void	check_unclosed_quotes(t_token **lst, char *content)
{
	char	quote_type;
	size_t	quote_count;
	size_t	i;

	if (content[0] == '"')
		quote_type = '"';
	else if (content[0] == '\'')
		quote_type = '\'';
	else
		return ;
	quote_count = 0;
	i = 0;
	while (content[i])
	{
		if (quote_type == '"' && content[i] == '"')
			quote_count++;
		else if (quote_type == '\'' && content[i] == '\'')
			quote_count++;
		i++;
	}
	if (quote_count % 2 != 0)
		exit(error_parser(lst));
}
