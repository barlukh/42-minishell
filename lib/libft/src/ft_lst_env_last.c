/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env_last.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:26:01 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/22 15:08:40 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_env	*ft_lst_env_last(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
