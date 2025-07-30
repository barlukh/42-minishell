/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isexpexception.c.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:12:12 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/30 10:22:49 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isexpexception(char *content, char quote, size_t i)
{
	if (content[i + 1] == '\0' || (ft_isquote(content[i + 1]) && quote != '\0'))
		return (true);
	return (false);
}
