/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:35:08 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/11 16:36:28 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	expand(char **input, char *tok_key, size_t *i, t_data *data);
static char	*define_key(char *input_orig, char *input, int *fd, t_data *data);
static void	exp_var(char *input, char *new_input, size_t i, t_env *current);
static void	rem_var(char *input, char **tok_key, size_t i);

void	expand_write(char *input, int *fd, t_token *current, t_data *data)
{
	char	*tok_key;
	size_t	i;

	if (current->type == TOK_HERE_UNQTD)
	{
		i = 0;
		while (input[i])
		{
			if (input[i] == '$' && (input[i + 1] == '?'
					|| ft_isalnum(input[i + 1]) || input[i + 1] == '_'))
			{
				tok_key = define_key(input, input + i + 1, fd, data);
				if (ft_strcmp("?", tok_key) == 0)
				{
					if (exp_exit_heredoc(&input, tok_key, i, data) != SUCCESS)
						error_heredoc_exp(input, fd, data);
				}
				else if (expand(&input, tok_key, &i, data) != SUCCESS)
					error_heredoc_exp(input, fd, data);
			}
			else
				i++;
		}
	}
	heredoc_write(input, fd);
}

// Allocates key (string) out of a token.
static char	*define_key(char *input_orig, char *input, int *fd, t_data *data)
{
	char	*tok_key;
	size_t	i;

	i = 0;
	if (input[i] == '?' || ft_isdigit(input[i]))
		i++;
	else
		while (ft_isalnum(input[i]) || input[i] == '_')
			i++;
	tok_key = ft_substr(input, 0, i);
	if (!tok_key)
		error_heredoc_exp(input_orig, fd, data);
	return (tok_key);
}

// Expands environment variables.
static bool	expand(char **input, char *tok_key, size_t *i, t_data *data)
{
	char	*new_input;
	t_env	*current;

	current = data->lst_env;
	while (current)
	{
		if (ft_strcmp(current->key, tok_key) == 0)
		{
			free(tok_key);
			tok_key = NULL;
			new_input = malloc(sizeof(char) * (ft_strlen(*input)
						+ ft_strlen(current->value) - ft_strlen(current->key)));
			if (!new_input)
				return (FAILURE);
			exp_var(*input, new_input, *i, current);
			*i += ft_strlen(current->value);
			*input = new_input;
			return (SUCCESS);
		}
		current = current->next;
	}
	rem_var(*input, &tok_key, *i);
	return (SUCCESS);
}

// Replaces variables with their expanded values.
static void	exp_var(char *input, char *new_input, size_t i, t_env *current)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	ft_memcpy(new_input, input, i);
	j = i;
	while (current->value[k])
		new_input[j++] = current->value[k++];
	i += ft_strlen(current->key) + 1;
	while (input[i])
		new_input[j++] = input[i++];
	new_input[j] = '\0';
	free(input);
	input = NULL;
}

// Removes variables that have no values.
static void	rem_var(char *input, char **tok_key, size_t i)
{
	size_t	len;

	len = ft_strlen(*tok_key) + 1;
	while (input[i + len] != '\0')
	{
		input[i] = input[i + len];
		i++;
	}
	input[i] = '\0';
	free(*tok_key);
	*tok_key = NULL;
}
