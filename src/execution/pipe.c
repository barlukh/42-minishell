
#include "minishell.h"

int	redirections_io(t_exec *current, int i, t_data *data)
{
	int cmds;
	int actual;
	int previous;

	actual = i % 2;
	previous = (i + 1) % 2;
	cmds = data->cmd_count;
	if (i == 0)
		dup_io(current->infile, STDIN_FILENO);
	else
		dup_io(data->pipe_fd1[0], STDIN_FILENO); //from pipe
	if (i == cmds -1)
	{
		if (current->outfile != 0)
			dup_io(current->outfile, STDOUT_FILENO);
	}
	else
		dup_io(data->pipe_fd2[1], STDOUT_FILENO); //from pipe
	// if (i != 0)
	// {
	// 	if (get_data()->pipe_fd[previous][0] != STDIN_FILENO)
	// 		close(get_data()->pipe_fd[previous][0]);
	// 	if (get_data()->pipe_fd[previous][1] != STDOUT_FILENO)
	// 		close(get_data()->pipe_fd[previous][1]);
	// }
	// if (i != 0 && i == cmds - 1)
	// {
	// 	if (get_data()->pipe_fd[actual][0] != STDIN_FILENO)
	// 		close(get_data()->pipe_fd[actual][0]);
	// 	if (get_data()->pipe_fd[actual][1] != STDOUT_FILENO)
	// 		close(get_data()->pipe_fd[actual][1]);
	// }
	return (0);
}

int	open_pipes(t_data *data)
{
	 pipe(data->pipe_fd1);
	 pipe(data->pipe_fd2);
	 return 0;
}
int	update_pipes(int pipe_fd[2][2], int i, int num_cmds)
{
	int current;

	current = i % 2;
	if (i != num_cmds - 1)
	{
		if (pipe(pipe_fd[current]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

int	open_fds_in(t_exec *current)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (current->red_in[i])
		i++;
	while (current->red_in[j])
	{
		current->infile = xopen(current->red_in[j], true);
		if (i != 1 && j != i - 1)
			close(current->infile);
		j++;
	}
	return (0);
}

int	open_fds_out(t_exec *current)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (current->red_out[i])
		i++;
	while (current->red_out[j])
	{
		current->outfile = xopen(current->red_out[j], false);
		if (i != 1 && j != i - 1)
			close(current->outfile);
		j++;
	}
	return (0);
}
