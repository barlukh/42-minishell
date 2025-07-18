/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_multiple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:27:20 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/18 14:37:38 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	count_words(char const *s, char *charset);
static int		is_delimiter(char c, char *charset);
static char		**split(char const *s, char *charset, char **arr);
static char		*allocate_word(char const *s, char *charset);

char	**ft_split_multiple(char const *s, char *charset)
{
	char	**arr;
	size_t	count;

	if (!s || !charset)
		return (NULL);
	count = count_words(s, charset);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	arr = split(s, charset, arr);
	if (!arr)
		return (NULL);
	return (arr);
}

// Counts how many words to split the string into.
static size_t	count_words(char const *s, char *charset)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && is_delimiter(*s, charset))
			s++;
		if (*s)
		{
			count++;
			while (*s && !is_delimiter(*s, charset))
				s++;
		}
	}
	return (count);
}

// Checks if a character is in a delimiter charset.
static int	is_delimiter(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (true);
		charset++;
	}
	return (false);
}

// Runs the main loop for splitting a string.
static char	**split(char const *s, char *charset, char **arr)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s && is_delimiter(*s, charset))
			s++;
		if (*s)
		{
			arr[i] = allocate_word(s, charset);
			if (!arr[i])
			{
				ft_free_array_index(arr, i);
				return (NULL);
			}
			i++;
			while (*s && !is_delimiter(*s, charset))
				s++;
		}
	}
	arr[i] = NULL;
	return (arr);
}

// Allocates an array for each word and copies the characters.
static char	*allocate_word(char const *s, char *charset)
{
	char	*start;
	char	*word;
	size_t	len;

	len = 0;
	start = (char *)s;
	while (*s && !is_delimiter(*s, charset))
	{
		len++;
		s++;
	}
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (start < s)
	{
		*word = *start;
		word++;
		start++;
	}
	*word = '\0';
	return (word - len);
}
