/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:42:57 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/25 15:20:38 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_oldpwd(char *cwd, t_data *data);

char	*oldpwd_get(t_data *data)
{
	char	*oldpwd;
	t_env	*current;

	current = data->lst_env;
	while (current)
	{
		if (ft_strcmp("OLDPWD", current->key) == 0)
		{
			oldpwd = current->value;
			return (oldpwd);
		}
		current = current->next;
	}
	return (NULL);
}

bool	oldpwd_set(char *cwd, t_data *data)
{
	t_env	*current;

	current = data->lst_env;
	while (current)
	{
		if (ft_strcmp("OLDPWD", current->key) == 0)
		{
			free(current->value);
			current->value = cwd;
			data->exit_status = 0;
			return (true);
		}
		current = current->next;
	}
	create_oldpwd(cwd, data);
	data->exit_status = 0;
	return (true);
}

// Creates a new key-value pair for OLDPWD in env.
static void	create_oldpwd(char *cwd, t_data *data)
{
	char	*key;
	t_env	*node;

	key = NULL;
	key = ft_strdup("OLDPWD");
	if (!key)
		error_lst_env(key, cwd, data);
	node = ft_lst_env_new(key, cwd);
	if (!node)
		error_lst_env(key, cwd, data);
	node->assigned = true;
	ft_lst_env_add_back(&data->lst_env, node);
}
