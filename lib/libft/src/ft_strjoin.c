/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:26:59 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/27 12:22:49 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*array;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	array = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!array)
		return (NULL);
	ft_memcpy(array, s1, s1_len);
	ft_memcpy(array + s1_len, s2, s2_len);
	array[s1_len + s2_len] = '\0';
	return (array);
}
