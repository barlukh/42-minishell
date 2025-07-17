/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:18:31 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/17 11:04:35 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

//Erase n bytes data from pointer s writing 0 instead starting from s

void	ft_bzero(void *s, size_t n)
{
	char	*temp_ptr;

	temp_ptr = (char *) s;
	while (n > 0)
	{
		*(temp_ptr++) = 0;
		n--;
	}
}
