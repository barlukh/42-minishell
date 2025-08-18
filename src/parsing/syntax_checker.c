/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:59:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/18 12:06:11 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_valid_quotes(char *content);
static bool	has_valid_pipes(t_token *current, t_data *data);
static bool	has_valid_redirs(t_token *current);
static bool	is_ambiguous_exp(t_token *current);

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
		ft_putendl_fd(ERR_MSG_QUOTE, STDERR_FILENO);
		return (false);
	}
	return (true);
}

// Checks for valid pipes.
static bool	has_valid_pipes(t_token *current, t_data *data)
{
	if (current == data->lst_tok)
	{
		ft_putendl_fd(ERR_MSG_PIPES, STDERR_FILENO);
		return (false);
	}
	if (current->next == NULL)
	{
		ft_putendl_fd(ERR_MSG_PIPES, STDERR_FILENO);
		return (false);
	}
	if (current->next->type == TOK_PIPE)
	{
		ft_putendl_fd(ERR_MSG_PIPES, STDERR_FILENO);
		return (false);
	}
	return (true);
}

// Checks for valid redirections.
static bool	has_valid_redirs(t_token *current)
{
	if (current->next == NULL)
	{
		ft_putendl_fd(ERR_MSG_REDIR, STDERR_FILENO);
		return (false);
	}
	if (current->next->type != TOK_WORD)
	{
		ft_putendl_fd(ERR_MSG_REDIR, STDERR_FILENO);
		return (false);
	}
	return (true);
}

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
	if (ft_strchr(current->content, ' ') != NULL)
		return (true);
	if (ft_strchr(current->content, '\t') != NULL)
		return (true);
	if (ft_strchr(current->content, '\n') != NULL)
		return (true);
	return (false);
}
