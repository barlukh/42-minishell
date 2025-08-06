/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:57:43 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/06 18:59:57 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	define_token(char *input, size_t i, size_t *len);
static void	create_token(char *input, size_t i, size_t len, t_data *data);
static void	assign_token_type(char *content, t_token *node);

void	tokenizer(char *input, t_data *data)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (input[i])
	{
		len = 0;
		if (ft_isifs(input[i]))
		{
			i++;
			continue ;
		}
		define_token(input, i, &len);
		create_token(input, i, len, data);
		i += len;
	}
	free(input);
	input = NULL;
}

// Defines the length of a token.
static void	define_token(char *input, size_t i, size_t *len)
{
	char	quote;

	quote = '\0';
	while (input[i])
	{
		if (quote == '\0' && ft_isquote(input[i]))
			quote = input[i];
		else if (input[i] == quote)
			quote = '\0';
		else if (quote == '\0' && ft_isdelimiter(input, i, len))
			return ;
		i++;
		(*len)++;
	}
}

// Creates a token using ft_substr() and appends it as a node to a linked list.
static void	create_token(char *input, size_t i, size_t len, t_data *data)
{
	char	*content;
	t_token	*node;

	content = ft_substr(input, i, len);
	if (!content)
		error_tok(input, data);
	node = ft_lst_tok_new(content);
	if (!node)
	{
		free(content);
		content = NULL;
		error_tok(input, data);
	}
	assign_token_type(content, node);
	ft_lst_tok_add_back(&data->lst_tok, node);
}

// Assigns each token its type.
static void	assign_token_type(char *content, t_token *node)
{
	if (ft_strcmp(content, "|") == 0)
		node->type = TOK_PIPE;
	else if (ft_strcmp(content, "<") == 0)
		node->type = TOK_IN;
	else if (ft_strcmp(content, ">") == 0)
		node->type = TOK_OUT;
	else if (ft_strcmp(content, "<<") == 0)
		node->type = TOK_HERE;
	else if (ft_strcmp(content, ">>") == 0)
		node->type = TOK_APP;
	else
		node->type = TOK_WORD;
}
