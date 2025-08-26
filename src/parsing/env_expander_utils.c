/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:04:56 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/26 16:05:44 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exp_loop(char *new_cont, size_t *j, size_t *k, t_env *current);

void	var_exp_q(char *content, char *new_cont, size_t *i, t_env *current)
{
	size_t	j;
	size_t	k;

	j = *i;
	k = 0;
	ft_memcpy(new_cont, content, *i);
	while (current->value[k])
		new_cont[j++] = current->value[k++];
	k = j;
	*i += ft_strlen(current->key) + 1;
	while (content[*i])
		new_cont[j++] = content[(*i)++];
	new_cont[j] = '\0';
	*i = k;
	free(content);
}

void	var_exp_u(char *content, char *new_cont, size_t *i, t_env *current)
{
	size_t	j;
	size_t	k;

	j = *i;
	k = 0;
	ft_memcpy(new_cont, content, *i);
	exp_loop(new_cont, &j, &k, current);
	k = j;
	*i += ft_strlen(current->key) + 1;
	while (content[*i])
		new_cont[j++] = content[(*i)++];
	new_cont[j] = '\0';
	*i = k;
	free(content);
}

// Helper function containing the expansion loop for var_exp_u() function.
static void	exp_loop(char *new_cont, size_t *j, size_t *k, t_env *current)
{
	int		in;

	in = 0;
	while (current->value[*k])
	{
		if (ft_isifs(current->value[*k]))
		{
			if (current->value[*k + 1] == '\0')
			{
				new_cont[(*j)++] = ' ';
				break ;
			}
			if (in && !ft_isifs(current->value[*k + 1]))
				new_cont[(*j)++] = ' ';
			(*k)++;
			continue ;
		}
		new_cont[(*j)++] = current->value[(*k)++];
		in = 1;
	}
}

void	var_remove(char *content, char **tok_key, size_t i)
{
	size_t	len;

	len = ft_strlen(*tok_key) + 1;
	while (content[i + len] != '\0')
	{
		content[i] = content[i + len];
		i++;
	}
	content[i] = '\0';
	free(*tok_key);
	*tok_key = NULL;
}
