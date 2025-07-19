/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:19:51 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/19 13:46:45 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_back(t_token **lst, t_token *node)
{
	t_token	*last;

	if (!lst || !node)
		return ;
	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = node;
}
