/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:22:28 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/29 11:44:59 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	expand(char **content, size_t i, t_env **lst_env);
static char	*define_key(char *content);
static void	exp_var(char *content, char *new_content, size_t i, t_env *current);
static void	rem_var(char *content, char **tok_key, size_t i);

bool	env_expander(t_env **lst_env, t_token **lst_tok)
{
	char	quote;
	size_t	i;
	t_token	*current;

	current = *lst_tok;
	while (current)
	{
		quote = '\0';
		i = 0;
		while (current->content[i])
		{
			if (ft_isexpandable(current->content[i], &quote) == true)
			{
				if (ft_isquotenull(current->content[i + 1]))
					break ;
				if (expand(&current->content, i, lst_env) != SUCCESS)
					return (FAILURE);
			}
			else
				i++;
		}
		current = current->next;
	}
	return (SUCCESS);
}

// Expands environment variables.
static bool	expand(char **content, size_t i, t_env **lst_env)
{
	char	*tok_key;
	char	*new_content;
	t_env	*current;

	tok_key = define_key(*content + i + 1);
	if (!tok_key)
		return (FAILURE);
	current = *lst_env;
	while (current)
	{
		if (ft_strcmp(current->key, tok_key) == 0)
		{
			free(tok_key);
			new_content = malloc(sizeof(char) * (ft_strlen(*content)
						+ ft_strlen(current->value) - ft_strlen(current->key)));
			if (!new_content)
				return (FAILURE);
			exp_var(*content, new_content, i, current);
			*content = new_content;
			return (SUCCESS);
		}
		current = current->next;
	}
	rem_var(*content, &tok_key, i);
	return (SUCCESS);
}

// Allocates key (string) out of a token.
static char	*define_key(char *content)
{
	char	*tok_key;
	size_t	i;

	i = 0;
	while (content[i])
	{
		if (ft_isalnum(content[i]) || content[i] == '_')
			i++;
		else
			break ;
	}
	tok_key = ft_substr(content, 0, i);
	if (!tok_key)
		return (NULL);
	return (tok_key);
}

// Replaces variables with their expanded values.
static void	exp_var(char *content, char *new_content, size_t i, t_env *current)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (j < i)
	{
		new_content[j] = content[j];
		j++;
	}
	while (current->value[k])
	{
		new_content[j] = current->value[k];
		j++;
		k++;
	}
	i += (ft_strlen(current->key) + 1);
	while (content[i] != '\0')
	{
		new_content[j] = content[i];
		i++;
		j++;
	}
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
