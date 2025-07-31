/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_finalizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:47:26 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/31 18:04:12 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_finalizer(t_data *data)
{
	t_token	*current;
	t_token	*next;

	current = data->lst_tok;
	while (current)
	{
		next = current->next;
		if (current->content[0] == '\0')
			ft_lst_tok_remove(&data->lst_tok, current);
		current = next;
	}
}
