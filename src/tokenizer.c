/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:57:43 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/20 15:26:51 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	define_quoted_token(char *input, size_t i, size_t *len);
static void	define_unquoted_token(char *input, size_t i, size_t *len);
static void	create_token(char *input, t_token **lst, size_t i, size_t len);

void	tokenizer(char *input, t_token **lst)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (input[i] != '\0')
	{
		len = 0;
		if (input[i] == '"')
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
	while (input[i] != '\0')
	{
		i++;
		(*len)++;
		if (input[i] == '"')
		{
			(*len)++;
			break ;
		}
	}
}

static void	define_unquoted_token(char *input, size_t i, size_t *len)
{
	size_t	j;

	while (input[i] != '\0' && input[i] != '"')
	{
		j = 0;
		while (DELIMITERS[j] != '\0')
		{
			if (input[i] == DELIMITERS[j])
			{
				if (*len == 0)
					*len = 1;
				return ;
			}
			j++;
		}
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
	ft_lstadd_back(lst, node);
}
