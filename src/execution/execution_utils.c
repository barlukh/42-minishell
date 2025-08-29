/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:30:43 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/29 10:57:30 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_env_rebuild(char **env, t_data *data);

char	**rebuild_env(t_data *data)
{
	char	**env;
	char	*key_eq;
	size_t	i;
	t_env	*current;

	env = malloc(sizeof(char *) * (ft_lst_env_size(data->lst_env) + 1));
	if (!env)
		error_general_mem(data);
	i = 0;
	current = data->lst_env;
	while (current)
	{
		key_eq = ft_strjoin(current->key, "=");
		if (!key_eq)
			error_env_rebuild(env, data);
		env[i] = ft_strjoin(key_eq, current->value);
		free(key_eq);
		if (!env[i])
			error_env_rebuild(env, data);
		i++;
		current = current->next;
	}
	env[i] = NULL;
	return (env);
}

// Handles errors in rebuild_env() function.
static void	error_env_rebuild(char **env, t_data *data)
{
	ft_lst_env_clear(&data->lst_env);
	data->lst_env = NULL;
	ft_lst_exec_clear(&data->lst_exec);
	data->lst_exec = NULL;
	ft_free_array(env);
	clear_history();
	ft_putendl_fd(ERR_MSG_MEM, STDERR_FILENO);
	data->exit_status = 1;
	exit(data->exit_status);
}
