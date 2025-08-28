/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isexpexception.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:12:12 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/28 14:14:24 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isexpexception(char *content, char quote, size_t i)
{
	char	next;

	next = content[i + 1];
	if (next == '\0')
		return (true);
	if (quote != '\0')
	{
		if (next == '?' || next == '_' || ft_isalpha(next))
			return (false);
		else
			return (true);
	}
	return (false);
}
