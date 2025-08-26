#include "minishell.h"

void	execution(t_data *data)
{
	t_exec		*node;
	int			i;
	char		**env;
	int		tmp_fd[2];
	int		pipefd_read;
	int		pipefd_write;

	i = 0;
	node = data->lst_exec;
	env = rebuild_env(*data->lst_env, i, i);
	while (node)
	{
		initialize_execution(data, tmp_fd, i);
		if (i % 2 == 0)
		{
			pipefd_read = data->pipe_b[0];
			pipefd_write = data->pipe_a[1];
		}
		else
		{
			pipefd_read = data->pipe_a[0];
			pipefd_write = data->pipe_b[1];
		}
		open_fds_in(node);								
		open_fds_out(node, i);								
		if (builtins_check(node, data))
			builting_process(node, i, data, tmp_fd);
		else 
			child_process(node, i, env, data, tmp_fd, pipefd_read, pipefd_write);
		// update_pipes(data->pipe_fd, i, data->cmd_count, tmp_fd);
		node= node->next;
		i++;
	}
	wait_process(data->pids, data);
}

void	initialize_execution(t_data *data, int *tmp_fd, int i)
{
	(void)tmp_fd;
	ft_memset(data->pipe_a, -1, sizeof(int) * 2);
	ft_memset(data->pipe_b, -1, sizeof(int) * 2);
	data->pids = ft_calloc(sizeof(pid_t), data->cmd_count);
	if (data->pids == NULL) {
		perror("malloc failed for pids");
		exit(EXIT_FAILURE);
	}
	if (data->cmd_count > 1 && i % 2 == 0)
	{
		if (pipe(data->pipe_a) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (pipe(data->pipe_b) == -1)
		{
			perror("pipe error:");
			exit(EXIT_FAILURE);
		}
	}
}

int	child_process(t_exec *node, int i, char **env, t_data *data, int *tmp_fd, int pipefd_read, int pipefd_write)
{
	char	*path;

	(void)tmp_fd;
	path = NULL;
	data->pids[i] = fork();
	if (data->pids[i] < 0)
	{
		perror("fork error:");
		exit(EXIT_FAILURE);
	}
	if (data->pids[i] == 0)
	{
		redirections_io(node, i, pipefd_read, pipefd_write);
		// if (i % 2 == 0)
		// 	redirections_io(node, i, pipefd_read, pipefd_write);
		// else
		// 	redirections_io(node, i, data->pipe_b, data->pipe_a);
		path = path_finder(node->cmd_arg, env);
		if (execve(path, node->cmd_arg, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		free(env);
	}
	// if (i % 2 == 0)
	// {
	// 	if (data->pipe_a[0] != -1)
	// 		safe_close(&data->pipe_a[0]);
	// 	if (data->pipe_b[1] != -1)
	// 		safe_close(&data->pipe_b[1]);
	// }
	// else
	// {
	// 	if (data->pipe_a[1] != -1)
	// 		safe_close(&data->pipe_a[1]);
	// 	if (data->pipe_b[0] != -1)
	// 		safe_close(&data->pipe_b[0]);
	// }
	return (0);
}

int	builting_process(t_exec *node, int i, t_data *data, int *tmp_fd)
{
	(void)tmp_fd;
	(void)data;
	(void)node;
	(void)i;
	// redirections_io(node, i, pipefd_read, pipefd_write);
	return (0);
}
