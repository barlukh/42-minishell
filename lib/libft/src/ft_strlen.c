/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:20:32 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/17 11:06:02 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// The strlen() function calculates the length of the string pointed to by s, 
// excluding the terminating null byte ('\0').

size_t	ft_strlen(const char *s)
{
	int	p;

	p = 0;
	while (*s++)
		++p;
	return (p);
}
