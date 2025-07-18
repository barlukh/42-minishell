/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:57:43 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/18 17:53:38 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	create_token(t_list **input_head, char *input_line, size_t i);

void	tokenize_input(t_list **input_head, char *input_line)
{
	size_t	i;

	i = 0;
	while (input_line[i] != '\0')
	{
		create_token(input_head, input_line, i);
		i++;
	}
	free(input_line);
}

static void create_token(t_list **input_head, char *input_line, size_t i)
{
	char	*content;
	t_list	*node;

	content = ft_substr(input_line, i, 1);
	if (!content)
	{
		free(input_line);
		ft_lstclear(input_head);
		exit(1);
	}
	node = ft_lstnew(content);
	ft_lstadd_back(input_head, node);
}
