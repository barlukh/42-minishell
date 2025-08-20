
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
		// update_pipes(current->pipe_fd, i, data->cmd_count); // update_pipe on parent side
		if (builtins_check(current, data)) // check if cmd is a builting
			builting_process(current, i);
		else
			child_process(current, i, env);
		current= current->next;
		i++;
	}
	wait_process(data->pids, data);
}

int	builting_process(t_exec *current, int i)
{
	redirections_io(current, i); // resets the reclying system of pipes
	return (0);
}

int	child_process(t_exec *current, int i, char **env)
{
	char	*path;
	int		previous;

	path = NULL;
	previous = (i + 1) % 2;
	open_fds_in(current);								
	update_pipes(current->pipe_fd, i); // update_pipe on parent side
	get_data()->pids[i] = fork();
	if (get_data()->pids[i] < 0)
	{
		perror("fork error:");
		exit(EXIT_FAILURE);
	}
	open_fds_out(current);								
	if (get_data()->pids[i] == 0) // child process
	{
		// resets the reclying system of pipes
		redirections_io(current, i); // TODO:

		// solve paths.
		path = path_finder(current->cmd_arg, env); // TODO:
		execve(path, current->cmd_arg, env);
		free(env);
	}
	if (i != 0)
	{
		close(current->pipe_fd[previous][0]);
		close(current->pipe_fd[previous][1]);
	}
	return (0);
}
