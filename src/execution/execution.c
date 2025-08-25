#include "minishell.h"

void	execution(t_data *data)
{
	t_exec		*node;
	int			i;
	char		**env;
	int		tmp_fd[2];

	i = 0;
	node = data->lst_exec;
	env = rebuild_env(*data->lst_env, i, i);
	initialize_execution(data, tmp_fd);
	while (node)
	{
		open_fds_in(node);								
		open_fds_out(node, i);								
		if (builtins_check(node, data))
			builting_process(node, i, data, tmp_fd);
		else 
			child_process(node, i, env, data, tmp_fd);
		update_pipes(data->pipe_fd, i, data->cmd_count, tmp_fd);
		node= node->next;
		i++;
	}
	wait_process(data->pids, data);
}

void	initialize_execution(t_data *data, int *tmp_fd)
{
	ft_memset(data->pipe_fd, -1, sizeof(int) * 2);
	ft_memset(tmp_fd, -1, sizeof(int) * 2);
	data->pids = ft_calloc(sizeof(pid_t), data->cmd_count);
	if (data->pids == NULL) {
		perror("malloc failed for pids");
		exit(EXIT_FAILURE);
	}
	if (data->cmd_count > 1)
	{
		if (pipe(data->pipe_fd) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		if (pipe(tmp_fd) == -1)
		{
			perror("pipe error:");
			exit(EXIT_FAILURE);
		}
	}
}

int	child_process(t_exec *node, int i, char **env, t_data *data, int *tmp_fd)
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
		redirections_io(node, i, data, tmp_fd);
		path = path_finder(node->cmd_arg, env);
		if (execve(path, node->cmd_arg, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		free(env);
	}
	// if (node->infile != -1)
	// 	safe_close(&node->infile);
	// if (node->outfile != -1)
	// 	safe_close(&node->outfile);
	if (data->pipe_fd[READ] != -1)
		safe_close(&data->pipe_fd[READ]);
	// if (data->cmd_count > 1)
	// 	data->pipe_fd[READ] = tmp_fd[READ];
	// else
	// 	safe_close(&tmp_fd[READ]);
	safe_close(&tmp_fd[WRITE]);
	return (0);
}

int	builting_process(t_exec *node, int i, t_data *data, int *tmp_fd)
{
	redirections_io(node, i, data, tmp_fd); // resets the reclying system of pipes
	return (0);
}
