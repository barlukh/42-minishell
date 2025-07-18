/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_single.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:27:20 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/18 14:32:43 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	count_words(char const *s, char c);
static char		**allocate_array(char const *s, char c, char **arr);

char	**ft_split_single(char const *s, char c)
{
	char	**arr;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	arr = allocate_array(s, c, arr);
	if (!arr)
		return (NULL);
	arr[count] = NULL;
	return (arr);
}

// Counts how many words to split the string into.
static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

// Allocates each single word into its array.
static char	**allocate_array(char const *s, char c, char **arr)
{
	size_t	word_len;
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (ft_strchr(s, c))
				word_len = ft_strchr(s, c) - s;
			else
				word_len = ft_strlen(s);
			arr[i] = ft_substr(s, 0, word_len);
			if (!arr[i])
			{
				ft_free_array_index(arr, i);
				return (NULL);
			}
			s += word_len;
			i++;
		}
	}
	return (arr);
}
