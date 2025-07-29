/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:54:00 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/29 14:08:22 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_remover(t_data *data)
{
	char	quote;
	char	*read;
	char	*write;
	t_token	*current;

	current = data->lst_tok;
	while (current)
	{
		quote = '\0';
		read = current->content;
		write = current->content;
		while (*read)
		{
			if (quote == '\0' && ft_isquote(*read))
				quote = *read;
			else if (*read == quote)
				quote = '\0';
			else
				*write++ = *read;
			read++;
		}
		*write = '\0';
		current = current->next;
	}
}
