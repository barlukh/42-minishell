/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:26:45 by bgazur            #+#    #+#             */
/*   Updated: 2025/09/04 13:20:38 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*home_get(t_data *data)
{
	char	*home;
	t_env	*current;

	current = data->lst_env;
	while (current)
	{
		if (ft_strcmp("HOME", current->key) == 0)
		{
			home = current->value;
			return (home);
		}
		current = current->next;
	}
	return (NULL);
}

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

char	*pwd_get(t_data *data, t_exec *node)
{
	char	*pwd;
	t_env	*current;

	current = data->lst_env;
	while (current)
	{
		if (ft_strcmp("PWD", current->key) == 0)
		{
			pwd = ft_strdup(current->value);
			if (!pwd)
			{
				close_all_fds(data, node);
				error_general_mem(data);
			}
			return (pwd);
		}
		current = current->next;
	}
	return (NULL);
}
