
#include "minishell.h"

void	execution(t_data *data)
{
	int			i;
	char		**env;
	t_exec		*node;

	i = 0;
	node = data->lst_exec;
	env = rebuild_env(data);
	initialize_execution(data);
	ft_memset(node->fd, -1, sizeof(int) * 2);
	while (node)
	{
		if (get_data()->cmd_count > 1)
			pipe(node->fd);
		open_fds_in(node);								
		open_fds_out(node);								
		if (is_builtins(node->cmd_arg) == 1)
		{
			redirections_io(node, i);
			builtins_check(node, data);
		}
		else
			child_process(node, i, env, data);
		node= node->next;
		i++;
	}
	wait_process(data->pids, data);
}

void	initialize_execution(t_data *data)
{
	data->tmp_fd = dup(STDIN_FILENO);
	data->pids = ft_calloc(sizeof(pid_t), data->cmd_count);
	if (data->pids == NULL)
	{
		perror("malloc failed for pids");
		exit(EXIT_FAILURE);
	}
}

int	child_process(t_exec *node, int i, char **env, t_data *data)
{
	char	*path;

	path = NULL;
	data->pids[i] = fork();
	if (data->pids[i] < 0)
	{
		perror("fork error:");
		exit(EXIT_FAILURE);
	}
	if (data->pids[i] == 0)
	{
		redirections_io(node, i);
		path = path_finder(node->cmd_arg, env);
		if (path && access(path, X_OK) == 0)
		{
			execve(path, node->cmd_arg, env);
			perror(node->cmd_arg[0]);
			exit(EXIT_FAILURE);
		}
		perror(node->cmd_arg[0]);
		free(env);
		exit(127);
	}
	if (get_data()->cmd_count > 1)
	{
		safe_close(&node->fd[WRITE]);
		safe_close(&data->tmp_fd);
		data->tmp_fd = node->fd[READ];
	}
	return (0);
}
