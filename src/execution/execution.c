
#include "minishell.h"

void	execution(t_data *data)
{
	t_exec		*current;
	int			i;
	char		**env;

	i = 0;
	current = data->lst_exec;
	// Rebuild env from struct for execve
	env = rebuild_env(*data->lst_env, i, i);
	data->pids = malloc(sizeof(pid_t) * data->cmd_count);  // num_cmds is the number of commands in the pipeline
	if (data->pids == NULL) {
		perror("malloc failed for pids");
		exit(EXIT_FAILURE);
	}
	while (current)
	{
		// open_fds(*current); // inside child or builting
		open_fds_in(current);								
		open_fds_out(current);								
		update_pipes(data->pipe_fd, i, data->cmd_count); // update_pipe on parent side
		if (builtins_check(current, data)) // check if cmd is a builting
			builting_process(current, i, data);
		else 
			child_process(current, i, env, data);
		current= current->next;
		i++;
	}
	wait_process(data->pids, data);
}

int	builting_process(t_exec *current, int i, t_data *data)
{
	redirections_io(current, i, data); // resets the reclying system of pipes
	return (0);
}

int	child_process(t_exec *current, int i, char **env, t_data *data)
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
		// resets the reclying system of pipes
		redirections_io(current, i, data); // BUG:

		// solve paths.
		path = path_finder(current->cmd_arg, env); // TODO:
		execve(path, current->cmd_arg, env);
		free(env);
	}
	int prev = (i + 1) % 2;
	if (i != 0)
	{
		close(data->pipe_fd[prev][0]);
		close(data->pipe_fd[prev][1]);
	}
	return (0);
}
