/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:22:28 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/04 09:51:07 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand(char **content, size_t i, t_data *data);
static char	*define_key(char *content, t_data *data);
static void	exp_var(char *content, char *new_content, size_t i, t_env *current);
static void	rem_var(char *content, char **tok_key, size_t i);

void	env_expander(t_data *data)
{
	char	quote;
	size_t	i;
	t_token	*current;

	current = data->lst_tok;
	while (current)
	{
		quote = '\0';
		i = 0;
		while (current->content[i])
		{
			if (ft_isexpandable(current->content[i], &quote)
				&& !ft_isexpexception(current->content, quote, i))
				expand(&current->content, i, data);
			else
				i++;
		}
		current = current->next;
	}
}

// Expands environment variables.
static void	expand(char **content, size_t i, t_data *data)
{
	char	*tok_key;
	char	*new_content;
	t_env	*current;

	tok_key = define_key(*content + i + 1, data);
	if (ft_strcmp("?", tok_key) == 0)
		return (exp_exit_status(content, tok_key, i, data));
	current = data->lst_env;
	while (current)
	{
		if (ft_strcmp(current->key, tok_key) == 0)
		{
			free(tok_key);
			new_content = malloc(sizeof(char) * (ft_strlen(*content)
						+ ft_strlen(current->value) - ft_strlen(current->key)));
			if (!new_content)
				error_env_exp(data);
			exp_var(*content, new_content, i, current);
			*content = new_content;
			return ;
		}
		current = current->next;
	}
	rem_var(*content, &tok_key, i);
}

// Allocates key (string) out of a token.
static char	*define_key(char *content, t_data *data)
{
	char	*tok_key;
	size_t	i;

	i = 0;
	if (content[i] == '?' || ft_isdigit(content[i]))
		i++;
	else
		while (ft_isalnum(content[i]) || content[i] == '_')
			i++;
	tok_key = ft_substr(content, 0, i);
	if (!tok_key)
		error_env_exp(data);
	return (tok_key);
}

// Replaces variables with their expanded values.
static void	exp_var(char *content, char *new_content, size_t i, t_env *current)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	ft_memcpy(new_content, content, i);
	j = i;
	while (current->value[k])
		new_content[j++] = current->value[k++];
	i += ft_strlen(current->key) + 1;
	while (content[i])
		new_content[j++] = content[i++];
	new_content[j] = '\0';
	free(content);
}

// Removes variables that have no values.
static void	rem_var(char *content, char **tok_key, size_t i)
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
}
