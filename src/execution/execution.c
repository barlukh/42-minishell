
#include "../include/minishell.h"

void	error_msg(char *str);
int		open_fds(t_exec current);
int		xopen(const char *pathname);
int		update_pipes(int pipe_fd[2][2], int i, int num_cmds);
int		builting_process(t_exec current);
int		child_process(t_exec current);
bool	wait_process(pid_t *pid, t_data *data);

void	execution(t_data *data)
{
	t_exec		*current;
	int			i;

	i = 0;
	current = data->lst_exec;
	while (current)
	{
		open_fds(*current); // inside child or builting
		if (builtins_check()) // check if cmd is a builting
			builting_process(*current);
		else
			child_process(*current);
		update_pipes(); // update_pipe on parent side
		current= data->lst_exec->next;
		i++;
	}
	wait_process();
}

int	builting_process(t_exec current)
{
	redirections_io(current); // resets the reclying system of pipes
	return (0);
}

int	child_process(t_exec current)
{
	pid_t	pids;

	pids = fork();
	if (pids < 0)
	{
		perror("fork error:");
		exit(EXIT_FAILURE);
	}
	if (pids == 0) // child process
	{
		redirections_io(current); // resets the reclying system of pipes
	}
	return (0);
}

int	redirections_io(t_exec current)
{

}

int	update_pipes(int pipe_fd[2][2], int i, int num_cmds)
{
	int current;
	int previous;

	current = i % 2;
	previous = (i + 1) % 2;
	if (i != num_cmds - 1)
	{
		if (pipe(pipe_fd[current]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	if (i != 0)
	{
		close(pipe_fd[previous][0]);
		close(pipe_fd[previous][1]);
	}
	return (0);
}

int	open_fds(t_exec current)
{
	int i;

	i = 0;
	while (current.red_in[i])
	{
		current.red_in = xopen(current.red_in[i]); // open return int, red_in is of type char **
		i++;
	}
	i = 0;
	while (current.red_out[i])
	{
		current.red_out = xopen(current.red_out[i]); // open return int, red_in is of type char **

		i++;
	}
	return (0);
}

int	xopen(const char *pathname)
{
	int fd;

	fd = open(pathname, O_RDONLY);
	if (fd == -1) {
		error_msg("open failed");
		exit(EXIT_FAILURE);
	}
	return fd;
}

void	error_msg(char *str)
{
	perror(str);
}

// dup2 (red_in);
// dup2 (red_out);
//
// execve(data->cmd_arg, PATH, data->lst_env)


