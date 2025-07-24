/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:57:43 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/24 08:54:38 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	define_token(char *input, size_t i, size_t *len);
static int	create_token(char *input, size_t i, size_t len, t_token **lst_tok);
static void	assign_token_type(char *content, t_token *node);

int	tokenizer(char *input, t_token **lst_tok)
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
		if (create_token(input, i, len, lst_tok) != SUCCESS)
			return (FAILURE);
		i += len;
	}
	free(input);
	input = NULL;
	return (SUCCESS);
}

// Defines the length of a token.
static void	define_token(char *input, size_t i, size_t *len)
{
	char	quote;

	quote = '\0';
	while (input[i])
	{
		if (quote == '\0' && (input[i] == '\'' || input[i] == '"'))
		{
			quote = input[i];
			i++;
			(*len)++;
			continue ;
		}
		else if (input[i] == quote)
		{
			i++;
			(*len)++;
			return ;
		}
		else if (ft_isdelimiter(input, i, len) && quote == '\0')
			return ;
		i++;
		(*len)++;
	}
}

// Creates a token using ft_substr() and appends it as a node to a linked list.
static int	create_token(char *input, size_t i, size_t len, t_token **lst_tok)
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
		content = NULL;
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
