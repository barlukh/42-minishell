/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:59:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/29 14:13:28 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_valid_quotes(char *content);
static bool	has_valid_pipes(t_token *current, t_data *data);
static bool	has_valid_redirs(t_token *current);

bool	syntax_checker(t_data *data)
{
	int		count;
	t_token	*current;

	count = 0;
	current = data->lst_tok;
	while (current)
	{
		if (current->type == TOK_WORD
			&& has_valid_quotes(current->content) != true)
			return (FAILURE);
		else if (current->type == TOK_PIPE
			&& has_valid_pipes(current, data) != true)
			return (FAILURE);
		else if (current->type != TOK_WORD && current->type != TOK_PIPE
			&& has_valid_redirs(current) != true)
			return (FAILURE);
		if (current->type == TOK_HERE)
			count++;
		current = current->next;
	}
	if (count > 16)
		error_synt(data);
	return (SUCCESS);
}

// Checks for valid quotes.
static bool	has_valid_quotes(char *content)
{
	char	quote;

	quote = '\0';
	while (*content)
	{
		if (quote == '\0' && ft_isquote(*content))
			quote = *content;
		else if (*content == quote)
			quote = '\0';
		content++;
	}
	if (quote != '\0')
	{
		ft_putendl_fd(ERR_MSG_QUOTE, 2);
		return (false);
	}
	return (true);
}

// Checks for valid pipes.
static bool	has_valid_pipes(t_token *current, t_data *data)
{
	if (current == data->lst_tok)
	{
		ft_putendl_fd(ERR_MSG_PIPES, 2);
		return (false);
	}
	if (current->next == NULL)
	{
		ft_putendl_fd(ERR_MSG_PIPES, 2);
		return (false);
	}
	if (current->next->type == TOK_PIPE)
	{
		ft_putendl_fd(ERR_MSG_PIPES, 2);
		return (false);
	}
	return (true);
}

// Checks for valid redirections.
static bool	has_valid_redirs(t_token *current)
{
	if (current->next == NULL)
	{
		ft_putendl_fd(ERR_MSG_REDIR, 2);
		return (false);
	}
	if (current->next->type != TOK_WORD)
	{
		ft_putendl_fd(ERR_MSG_REDIR, 2);
		return (false);
	}
	return (true);
}
