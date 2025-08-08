/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_exit_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:55:35 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/08 19:27:10 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exp_var(char *input, char *new_input, char *exit_str, size_t i);

bool	exp_exit_heredoc(char **input, char *tok_key, size_t i, t_data *data)
{
	char	*exit_str;
	char	*new_input;

	free(tok_key);
	tok_key = NULL;
	exit_str = ft_itoa(data->exit_status);
	if (!exit_str)
		return (FAILURE);
	new_input = malloc(sizeof(char) * (ft_strlen(*input)
				+ ft_strlen(exit_str) - 1));
	if (!new_input)
	{
		free(exit_str);
		exit_str = NULL;
		return (FAILURE);
	}
	exp_var(*input, new_input, exit_str, i);
	free(*input);
	*input = new_input;
	free(exit_str);
	exit_str = NULL;
	return (SUCCESS);
}

// Replaces the question mark with the current exit code.
static void	exp_var(char *input, char *new_input, char *exit_str, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	ft_memcpy(new_input, input, i);
	j = i;
	while (exit_str[k])
		new_input[j++] = exit_str[k++];
	i += 2;
	while (input[i])
		new_input[j++] = input[i++];
	new_input[j] = '\0';
}
