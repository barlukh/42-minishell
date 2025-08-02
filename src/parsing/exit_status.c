/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:55:35 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/01 20:28:38 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exp_var(char *content, char *new_content, char *exit_str, size_t i);

void	exp_exit_status(char **content, char *tok_key, size_t i, t_data *data)
{
	char	*exit_str;
	char	*new_content;

	free(tok_key);
	exit_str = ft_itoa(data->exit_status);
	if (!exit_str)
		error_env_exp(data);
	new_content = malloc(sizeof(char) * (ft_strlen(*content)
				+ ft_strlen(exit_str) - 1));
	if (!new_content)
	{
		free(exit_str);
		error_env_exp(data);
	}
	exp_var(*content, new_content, exit_str, i);
	*content = new_content;
}

// Replaces the question mark with the current exit code.
static void	exp_var(char *content, char *new_content, char *exit_str, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	ft_memcpy(new_content, content, i);
	j = i;
	while (exit_str[k])
		new_content[j++] = exit_str[k++];
	i += 2;
	while (content[i])
		new_content[j++] = content[i++];
	new_content[j] = '\0';
	free(exit_str);
	free(content);
}
