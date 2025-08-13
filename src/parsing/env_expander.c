/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:22:28 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/13 14:07:53 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand(char quote, char **content, size_t *i, t_data *data);
static char	*define_key(char *content, t_data *data);
static void	mem(char **content, char **new_cont, t_env *current, t_data *data);

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
				expand(quote, &current->content, &i, data);
			else
				i++;
		}
		if (current->type == TOK_HERE && current->next)
			current = current->next->next;
		else
			current = current->next;
	}
}

// Expands environment variables.
static void	expand(char quote, char **content, size_t *i, t_data *data)
{
	char	*tok_key;
	char	*new_cont;
	t_env	*current;

	tok_key = define_key(*content + *i + 1, data);
	if (ft_strcmp("?", tok_key) == 0)
		return (exp_exit_main(content, tok_key, *i, data));
	current = data->lst_env;
	while (current)
	{
		if (ft_strcmp(current->key, tok_key) == 0)
		{
			free(tok_key);
			mem(content, &new_cont, current, data);
			if (quote == '\"')
				var_exp_q(*content, new_cont, i, current);
			else
				var_exp_u(*content, new_cont, i, current);
			*content = new_cont;
			return ;
		}
		current = current->next;
	}
	var_remove(*content, &tok_key, *i);
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

// Allocates memory for new_content.
static void	mem(char **content, char **new_cont, t_env *current, t_data *data)
{
	*new_cont = ft_calloc(sizeof(char), (ft_strlen(*content)
				+ ft_strlen(current->value) - ft_strlen(current->key) + 1));
	if (!*new_cont)
		error_env_exp(data);
}
