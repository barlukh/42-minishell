/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:59:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/21 15:10:06 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parser(t_token **lst)
{
	t_token	*current;

	current = *lst;
	while (current)
	{
		// if (current->type == TOKEN_WORD)
		// 	check_unclosed_quotes(current->content);
		current = current->next;
	}
}

// static void	check_unclosed_quotes(char *content)
// {

// }