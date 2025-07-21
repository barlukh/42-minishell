/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:40:06 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/21 12:01:06 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	test(t_token **lst);

int	main(void)
{
	char	*input;
	t_token	*lst;

	lst = NULL;
	while (true)
	{
		read_input(&input);
		parse_input(input, &lst);
		test(&lst);
		ft_lstclear(&lst);
	}
	return (EXIT_SUCCESS);
}

#include <stdio.h>
static void	test(t_token **lst)
{
	t_token	*current;

	current = *lst;
	while (current)
	{
		if (current->type == 0)
			printf("%-14s | %s\n", "PIPE", current->content);
		else if (current->type == 1)
			printf("%-14s | %s\n", "REDIR_IN", current->content);
		else if (current->type == 2)
			printf("%-14s | %s\n", "REDIT_OUT", current->content);
		else if (current->type == 3)
			printf("%-14s | %s\n", "REDIR_HEREDOC", current->content);
		else if (current->type == 4)
			printf("%-14s | %s\n", "REDIR_APPEND", current->content);
		else if (current->type == 5)
			printf("%-14s | %s\n", "WORD", current->content);
		current = current->next;
	}
}
