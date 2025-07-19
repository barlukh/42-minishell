/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:57:43 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/19 17:48:44 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	define_token(char *input_line, size_t i, size_t *len);
static void	create_token(char *input_line, t_token **lst, size_t i, size_t len);

void	tokenizer(char *input_line, t_token **lst)
{
	// int		flag_quotes;
	size_t	i;
	size_t	len;

	// flag_quotes = false;
	i = 0;
	while (input_line[i] != '\0')
	{
		// if (input_line[i] == '"')
		// 	write(1, "a\n", 2);
		if (input_line[i] == ' ')
		{
			i++;
			continue ;
		}
		len = 0;
		define_token(input_line, i, &len);
		create_token(input_line, lst, i, len);
		i += len;
	}
	free(input_line);
	input_line = NULL;
}

static void	define_token(char *input_line, size_t i, size_t *len)
{
	size_t	j;

	while (input_line[i] != '\0')
	{
		j = 0;
		while (DELIMS[j] != '\0')
		{
			if (input_line[i] == DELIMS[j])
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

static void	create_token(char *input_line, t_token **lst, size_t i, size_t len)
{
	char	*content;
	t_token	*node;

	content = ft_substr(input_line, i, len);
	if (!content)
		exit(error_tok(input_line, lst, content));
	node = ft_lstnew(content);
	if (!node)
		exit(error_tok(input_line, lst, content));
	ft_lstadd_back(lst, node);
	node->type = TOKEN_PIPE;
}
