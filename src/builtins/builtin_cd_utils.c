/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:42:57 by bgazur            #+#    #+#             */
/*   Updated: 2025/09/04 13:24:39 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_oldpwd(char *cwd, t_exec *node, t_data *data);
static void	create_oldpwd(char *cwd, t_exec *node, t_data *data);

bool	wd_set(char *cwd, t_exec *node, t_data *data)
{
	char	*new_pwd;
	t_env	*current;

	current = data->lst_env;
	while (current)
	{
		if (ft_strcmp("PWD", current->key) == 0)
		{
			new_pwd = getcwd(NULL, 0);
			if (!new_pwd)
			{
				ft_putstr_fd("cd: ", STDERR_FILENO);
				ft_putendl_fd(strerror(errno), STDERR_FILENO);
				break ;
			}
			free(current->value);
			current->value = new_pwd;
		}
		current = current->next;
	}
	set_oldpwd(cwd, node, data);
	return (true);
}

// Sets the OLDPWD value.
static void	set_oldpwd(char *cwd, t_exec *node, t_data *data)
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
			return ;
		}
		current = current->next;
	}
	create_oldpwd(cwd, node, data);
	data->exit_status = 0;
	return ;
}

// Creates a new key-value pair for OLDPWD in env.
static void	create_oldpwd(char *cwd, t_exec *node, t_data *data)
{
	char	*key;
	t_env	*node_cur;

	key = NULL;
	key = ft_strdup("OLDPWD");
	if (!key)
	{
		close_all_fds(data, node);
		error_lst_env(key, cwd, data);
	}
	node_cur = ft_lst_env_new(key, cwd);
	if (!node_cur)
	{
		close_all_fds(data, node);
		error_lst_env(key, cwd, data);
	}
	node_cur->assigned = true;
	ft_lst_env_add_back(&data->lst_env, node_cur);
}
