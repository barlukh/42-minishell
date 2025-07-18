/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:40:06 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/18 17:45:26 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	test(t_list **input_head);

int	main(void)
{
	t_list	*input_head;

	input_head = NULL;
	parse_input(&input_head);
	test(&input_head);
	ft_lstclear(&input_head);
	return (SUCCESS);
}

static void	test(t_list **input_head)
{
	t_list	*current;

	current = *input_head;
	while (current != NULL)
	{
		ft_putendl_fd(current->content, 1);
		current = current->next;
	}
}
