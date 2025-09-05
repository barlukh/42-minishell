/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:42:28 by edlucca           #+#    #+#             */
/*   Updated: 2025/09/04 16:42:49 by edlucca          ###   ########.fr       */
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

void	create_process(t_data *data, t_exec *node, int i)
{
	if (node->cmd_arg[0])
	{
		if (is_builtins(node->cmd_arg) == true)
			builtin_process(node, i, data);
		else
			child_process(node, i, data);
	}
	if (data->tok_count == 1 && data->tmp_fd > 2)
		safe_close(&data->tmp_fd);
}
