/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:57:43 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/22 15:54:15 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	define_quoted_token(char *input, size_t i, size_t *len);
static void	define_unquoted_token(char *input, size_t i, size_t *len);
static int	create_token(char *input, t_token **lst_tok, size_t i, size_t len);
static void	assign_token_type(char *content, t_token *node);

void	tokenizer(char *input, t_token **lst_tok, t_env **lst_env)
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
		if (create_token(input, lst_tok, i, len) == FAILURE)
			exit(error_tokenizer(input, lst_tok, lst_env));
		i += len;
	}
	free(input);
	input = NULL;
}

// Defines a length of a quoted token.
static void	define_quoted_token(char *input, size_t i, size_t *len)
{
	char	quote;

	quote = input[i];
	while (input[i])
	{
		i++;
		(*len)++;
		if (input[i] == quote)
		{
			(*len)++;
			break ;
		}
	}
}

// Defines a length of an unquoted token.
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

// Creates a token using ft_substr() and appends it as a node to a linked list.
static int	create_token(char *input, t_token **lst_tok, size_t i, size_t len)
{
	char	*content;
	t_token	*node;

	content = ft_substr(input, i, len);
	if (!content)
		return (FAILURE);
	node = ft_lst_tok_new(content);
	if (!node)
	{
		free(content);
		return (FAILURE);
	}
	assign_token_type(content, node);
	ft_lst_tok_add_back(lst_tok, node);
	return (SUCCESS);
}

// Assigns each token its type.
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
