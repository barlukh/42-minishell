/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:11:23 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/23 12:48:34 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_action(char *content, t_data *data);
static void	add_to_env(char *equal, char *key, char *value, t_data *data);
static void	finalize_flag_node(char *equal, t_env *node, t_data *data);

void	builtin_export_loop(bool *inv_id, char *content, t_data *data)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(content[i]) && content[i] != '_')
	{
		*inv_id = true;
		ft_putendl_fd(ERR_MSG_IDEN, STDERR_FILENO);
		return ;
	}
	else
	{
		while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
			i++;
	}
	if (content[i] != '\0' && content[i] != '=')
	{
		*inv_id = true;
		ft_putendl_fd(ERR_MSG_IDEN, STDERR_FILENO);
		return ;
	}
	export_action(content, data);
}

// Performs the export action.
static void	export_action(char *content, t_data *data)
{
	char	*equal;
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	equal = ft_strchr(content, '=');
	if (!equal)
	{
		key = ft_strdup(content);
		value = ft_strdup("");
	}
	else
	{
		key = ft_substr(content, 0, equal - content);
		value = ft_strdup(equal + 1);
	}
	if (!key || !value)
		error_lst_env(key, value, data);
	add_to_env(equal, key, value, data);
}

// Adds the exported variable to env.
static void	add_to_env(char *equal, char *key, char *value, t_data *data)
{
	t_env	*current;
	t_env	*node;

	current = data->lst_env;
	while (current)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			if (equal != NULL)
			{
				free(current->value);
				current->value = value;
				current->assigned = true;
			}
			else
				free(value);
			free(key);
			return ;
		}
		current = current->next;
	}
	node = ft_lst_env_new(key, value);
	if (!node)
		error_lst_env(key, value, data);
	finalize_flag_node(equal, node, data);
}

// Sets the flag and adds the node to env.
static void	finalize_flag_node(char *equal, t_env *node, t_data *data)
{
	if (!equal)
		node->assigned = false;
	else
		node->assigned = true;
	ft_lst_env_add_back(&data->lst_env, node);
}
