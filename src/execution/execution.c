
#include "minishell.h"

void	execution(t_data *data)
{
	t_exec		*current;
	int			i;
	char		**env;
	int		tmp_fd[2];

	i = 0;
	current = data->lst_exec;
	env = rebuild_env(*data->lst_env, i, i);
	data->pids = malloc(sizeof(pid_t) * data->cmd_count);
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
	while (current)
	{
		open_fds_in(current);								
		open_fds_out(current, i);								
		if (builtins_check(current, data))
			builting_process(current, i, data, tmp_fd);
		else 
			child_process(current, i, env, data, tmp_fd);
		update_pipes(data->pipe_fd, i, data->cmd_count, tmp_fd);
		current= current->next;
		i++;
	}
	wait_process(data->pids, data);
}

int	builting_process(t_exec *current, int i, t_data *data, int *tmp_fd)
{
	redirections_io(current, i, data, tmp_fd); // resets the reclying system of pipes
	return (0);
}

int	child_process(t_exec *current, int i, char **env, t_data *data, int *tmp_fd)
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
		redirections_io(current, i, data, tmp_fd); // BUG:
		path = path_finder(current->cmd_arg, env);
		if (execve(path, current->cmd_arg, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		free(env);
	}
	close(data->pipe_fd[READ]);
	close(data->pipe_fd[WRITE]);
	close(current->infile);
	close(current->outfile);
	return (0);
}
