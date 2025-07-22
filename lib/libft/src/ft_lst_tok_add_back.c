/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_tok_add_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:19:51 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/22 14:36:13 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lst_tok_add_back(t_token **lst, t_token *node)
{
	t_token	*last;

	if (!lst || !node)
		return ;
	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	last = ft_lst_tok_last(*lst);
	last->next = node;
}
