/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:20:15 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/22 16:36:23 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lst_env_clear(t_env **lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->key);
		tmp->key = NULL;
		free(tmp->value);
		tmp->value = NULL;
		free(tmp);
		tmp = NULL;
	}
	*lst = NULL;
}
