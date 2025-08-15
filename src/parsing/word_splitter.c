/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:16:49 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/15 11:13:15 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_ifs(size_t *i, t_token *current);
static void	define_token(char *content, size_t i, size_t *len);
static bool	create_token(size_t *i, size_t len, t_token *cr, t_token **lst_new);

void	word_splitter(t_data *data)
{
	size_t	i;
	size_t	len;
	t_token	*current;
	t_token	*lst_new;

	lst_new = NULL;
	current = data->lst_tok;
	while (current)
	{
		i = 0;
		while (current->content[i])
		{
			skip_ifs(&i, current);
			if (!current->content[i])
				break ;
			define_token(current->content, i, &len);
			if (len == 0)
				break ;
			if (create_token(&i, len, current, &lst_new) != SUCCESS)
				error_general_mem(data);
		}
		current = current->next;
	}
	ft_lst_tok_clear(&data->lst_tok);
	data->lst_tok = lst_new;
}

// Skips input field separators.
static void	skip_ifs(size_t *i, t_token *current)
{
	while (current->content[*i] && ft_isifs(current->content[*i]))
		(*i)++;
}

// Defines the length of a token.
static void	define_token(char *content, size_t start, size_t *len)
{
	char	quote;
	size_t	i;

	quote = '\0';
	i = start;
	*len = 0;
	while (content[i])
	{
		if (quote == '\0' && ft_isquote(content[i]))
			quote = content[i];
		else if (quote != '\0' && content[i] == quote)
			quote = '\0';
		else if (quote == '\0' && ft_isifs(content[i]))
			break ;
		i++;
		(*len)++;
	}
}

// Creates a token using ft_substr() and appends it as a node to a linked list.
static bool	create_token(size_t *i, size_t len, t_token *cr, t_token **lst_new)
{
	char	*new_content;
	t_token	*node;

	new_content = ft_substr(cr->content, *i, len);
	if (!new_content)
		return (FAILURE);
	node = ft_lst_tok_new(new_content);
	if (!node)
	{
		free(new_content);
		new_content = NULL;
		return (FAILURE);
	}
	node->type = cr->type;
	ft_lst_tok_add_back(lst_new, node);
	*i += len;
	return (SUCCESS);
}
