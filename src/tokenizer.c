/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:57:43 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/18 14:35:55 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenize_input(char *input_line)
{
	char	**input_split;
	size_t	i;

	input_split = ft_split_multiple(input_line, DELIMS);
	i = 0;
	while (input_split[i] != NULL)
	{
		ft_putendl_fd(input_split[i], 1);
		i++;
	}
	ft_free_array_full(input_split);
	free(input_line);
}
