/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:57:25 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/26 16:27:18 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	build_lst_env(char **env, t_data *data);
static void	create_pwd(t_data *data);

void	create_lst_env(char **env, t_data *data)
{
	bool	pwd_exists;
	t_env	*current;

	pwd_exists = false;
	if (env && *env)
	{
		build_lst_env(env, data);
		current = data->lst_env;
		while (current)
		{
			if (ft_strcmp("PWD", current->key) == 0)
			{
				pwd_exists = true;
				break ;
			}
			current = current->next;
		}
	}
	if (pwd_exists == false)
		create_pwd(data);
}

// Builds the list of environmental variables.
static void	build_lst_env(char **env, t_data *data)
{
	char	*equal;
	char	*key;
	char	*value;
	t_env	*node;

	key = NULL;
	value = NULL;
	while (*env)
	{
		equal = ft_strchr(*env, '=');
		if (!equal)
			continue ;
		key = ft_substr(*env, 0, equal - *env);
		if (!key)
			error_lst_env(key, value, data);
		value = ft_strdup(equal + 1);
		if (!value)
			error_lst_env(key, value, data);
		node = ft_lst_env_new(key, value);
		if (!node)
			error_lst_env(key, value, data);
		node->assigned = true;
		ft_lst_env_add_back(&data->lst_env, node);
		env++;
	}
}

// Creates PWD variable if it is missing.
static void	create_pwd(t_data *data)
{
	char	*key;
	char	*value;
	t_env	*node;

	key = NULL;
	value = NULL;
	key = ft_strdup("PWD");
	if (!key)
		error_lst_env(key, value, data);
	value = getcwd(NULL, 0);
	if (!value)
		error_lst_env(key, value, data);
	node = ft_lst_env_new(key, value);
	if (!node)
		error_lst_env(key, value, data);
	node->assigned = true;
	ft_lst_env_add_back(&data->lst_env, node);
}
