/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:59:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/29 11:59:27 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_valid_quotes(char *content);
static bool	has_valid_pipes(t_token *current, t_token **lst_tok);
static bool	has_valid_redirs(t_token *current);
static bool	has_valid_heredocs(int count);

bool	syntax_checker(t_token **lst_tok)
{
	int		count;
	t_token	*current;

	count = 0;
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
		if (current->type == TOK_HERE)
			count++;
		current = current->next;
	}
	if (has_valid_heredocs(count) != true)
		return (FAILURE);
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
static bool	has_valid_pipes(t_token *current, t_token **lst_tok)
{
	if (current == *lst_tok)
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

// Checks for valid heredoc redirections.
static bool	has_valid_heredocs(int count)
{
	if (count > 16)
	{
		ft_putendl_fd(ERR_MSG_HERED, 2);
		return (false);
	}
	return (true);
}
