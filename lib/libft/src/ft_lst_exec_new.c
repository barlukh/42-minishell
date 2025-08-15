/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_exec_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:28:38 by edlucca           #+#    #+#             */
/*   Updated: 2025/08/15 10:47:48 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_exec	*ft_lst_exec_new(char **cmd_arg, char **red_in, char **red_out)
{
	t_exec	*new_node;

	new_node = ft_calloc(1, sizeof(t_exec));
	if (!new_node)
		return (NULL);
	new_node->cmd_arg = cmd_arg;
	new_node->red_in = red_in;
	new_node->red_out = red_out;
	new_node->next = NULL;
	return (new_node);
}
