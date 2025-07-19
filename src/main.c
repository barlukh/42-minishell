/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:40:06 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/19 15:31:34 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	test(t_token **lst);

int	main(void)
{
	char	*input_line;
	t_token	*lst;

	lst = NULL;
	read_input(&input_line);
	parse_input(input_line, &lst);
	test(&lst);
	ft_lstclear(&lst);
	return (SUCCESS);
}

static void	test(t_token **lst)
{
	t_token	*current;

	current = *lst;
	while (current != NULL)
	{
		ft_putstr_fd(current->content, 1);
		// write(1, "@", 1);
		// ft_putnbr_fd(current->type, 1);
		write(1, "\n", 1);
		current = current->next;
	}
}
