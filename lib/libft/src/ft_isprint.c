/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:19:35 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/17 11:04:56 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

//Check for printable character including space

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
	{
		return (c);
	}
	return (0);
}
