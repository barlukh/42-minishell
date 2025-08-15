/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_exit_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:55:35 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/15 11:13:15 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exp_var(char *content, char *new_cont, char *exit_str, size_t i);

void	exp_exit_main(char **content, char *tok_key, size_t i, t_data *data)
{
	char	*exit_str;
	char	*new_cont;

	free(tok_key);
	tok_key = NULL;
	exit_str = ft_itoa(data->exit_status);
	if (!exit_str)
		error_general_mem(data);
	new_cont = malloc(sizeof(char) * (ft_strlen(*content)
				+ ft_strlen(exit_str) - 1));
	if (!new_cont)
	{
		free(exit_str);
		exit_str = NULL;
		error_general_mem(data);
	}
	exp_var(*content, new_cont, exit_str, i);
	free(*content);
	*content = new_cont;
	free(exit_str);
	exit_str = NULL;
}

// Replaces the question mark with the current exit code.
static void	exp_var(char *content, char *new_cont, char *exit_str, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	ft_memcpy(new_cont, content, i);
	j = i;
	while (exit_str[k])
		new_cont[j++] = exit_str[k++];
	i += 2;
	while (content[i])
		new_cont[j++] = content[i++];
	new_cont[j] = '\0';
}
