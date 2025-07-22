/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_tok_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:20:15 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/22 14:36:16 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lst_tok_clear(t_token **lst)
{
	t_token	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
	*lst = NULL;
}
