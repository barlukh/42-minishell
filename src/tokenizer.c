/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:57:43 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/21 11:26:13 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	define_quoted_token(char *input, size_t i, size_t *len);
static void	define_unquoted_token(char *input, size_t i, size_t *len);
static void	create_token(char *input, t_token **lst, size_t i, size_t len);
static void	assign_token_type(char *content, t_token *node);

void	tokenizer(char *input, t_token **lst)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (input[i])
	{
		len = 0;
		if (ft_isquote(input[i]))
			define_quoted_token(input, i, &len);
		else if (ft_isifs(input[i]))
		{
			i++;
			continue ;
		}
		else
			define_unquoted_token(input, i, &len);
		create_token(input, lst, i, len);
		i += len;
	}
	free(input);
	input = NULL;
}

static void	define_quoted_token(char *input, size_t i, size_t *len)
{
	char	quote_type;

	quote_type = input[i];
	while (input[i])
	{
		i++;
		(*len)++;
		if (input[i] == quote_type)
		{
			(*len)++;
			break ;
		}
	}
}

static void	define_unquoted_token(char *input, size_t i, size_t *len)
{
	while (input[i] && !ft_isquote(input[i]))
	{
		if (ft_isdelimiter(input, i, len))
			return ;
		i++;
		(*len)++;
	}
}

static void	create_token(char *input, t_token **lst, size_t i, size_t len)
{
	char	*content;
	t_token	*node;

	content = ft_substr(input, i, len);
	if (!content)
		exit(error_tok(input, lst, content));
	node = ft_lstnew(content);
	if (!node)
		exit(error_tok(input, lst, content));
	assign_token_type(content, node);
	ft_lstadd_back(lst, node);
}

static void	assign_token_type(char *content, t_token *node)
{
	if (ft_strcmp(content, "|") == 0)
		node->type = TOKEN_PIPE;
	else if (ft_strcmp(content, "<") == 0)
		node->type = TOKEN_REDIR_IN;
	else if (ft_strcmp(content, ">") == 0)
		node->type = TOKEN_REDIR_OUT;
	else if (ft_strcmp(content, "<<") == 0)
		node->type = TOKEN_REDIR_HEREDOC;
	else if (ft_strcmp(content, ">>") == 0)
		node->type = TOKEN_REDIR_APPEND;
	else
		node->type = TOKEN_WORD;
}
