/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:38:40 by edlucca           #+#    #+#             */
/*   Updated: 2025/09/04 16:45:35 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_execution(t_data *data, t_exec *node);
static void	execute_child(t_exec *node, int i, t_data *data);

void	execution(t_data *data)
{
	int			i;
	t_exec		*node;

	i = 0;
	node = data->lst_exec;
	if (!node)
		return ;
	data->env = rebuild_env(data);
	initialize_execution(data, node);
	while (node)
	{
		if (open_fds(node, i) == false)
		{
			i++;
			node = node->next;
			continue ;
		}
		create_process(data, node, i);
		node = node->next;
		i++;
	}
	wait_process(data->pids, data);
	ft_free_array(data->env);
	free(data->pids);
}

bool	open_fds(t_exec *node, int i)
{
	if (i != get_data()->tok_count - 1)
		pipe(node->fd);
	if (node->in_first == true)
	{
		if (open_fds_in(node) == false)
		{
			parent_fds(node);
			return (false);
		}
	}
	if (open_fds_out(node) == false)
	{
		parent_fds(node);
		return (false);
	}
	if (node->in_first == false)
	{
		if (open_fds_in(node) == false)
		{
			parent_fds(node);
			return (false);
		}
	}
	return (true);
}

static void	initialize_execution(t_data *data, t_exec *node)
{
	ft_memset(node->fd, -1, sizeof(int) * 2);
	node->infile = -1;
	node->outfile = -1;
	data->tmp_fd = dup(STDIN_FILENO);
	data->pids = ft_calloc(sizeof(pid_t), data->tok_count);
	if (data->pids == NULL)
	{
		safe_close(&data->tmp_fd);
		clean_and_exit(data, node, 127);
	}
}

void	child_process(t_exec *node, int i, t_data *data)
{
	data->pids[i] = fork();
	if (data->pids[i] < 0)
	{
		clean_and_exit(data, node, 1);
	}
	if (data->pids[i] == 0)
	{
		execute_child(node, i, data);
	}
	if (get_data()->tok_count > 1)
		parent_fds(node);
}

static void	execute_child(t_exec *node, int i, t_data *data)
{
	char			*is_path;
	char			*path;
	struct stat		sb;

	is_path = ft_strchr(node->cmd_arg[0], '/');
	path = NULL;
	signals_exec_child();
	redirections_io(node, i);
	path = path_finder(node->cmd_arg, data->env);
	if (!path || node->cmd_arg[0][0] == '\0')
		check_empty(node, data);
	else if (stat(path, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
			check_dir(is_path, node, data);
		else if (access(path, X_OK) != 0)
			check_access(is_path, node, data);
	}
	else
		check_cmd(node, data);
	execve(path, node->cmd_arg, data->env);
	perror(node->cmd_arg[0]);
	free(path);
	clean_and_exit(data, node, 126);
}
