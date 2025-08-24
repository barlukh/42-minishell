
#include "minishell.h"

int	redirections_io(t_exec *current, int i, t_data *data, int *tmp_fd)
{
	int cmds;

	cmds = data->cmd_count;
	if (cmds == 1 && (current->infile == 0 && current->outfile == 0))
		return (0);
	if (i == 0 && current->infile != 0) // first command
										// dup2(current->infile, STDIN_FILENO);
		dup_io(&current->infile, STDIN_FILENO);
	else
		dup2(data->pipe_fd[READ], STDIN_FILENO);
		// dup_io(&data->pipe_fd[READ], STDIN_FILENO);
	if (i == cmds - 1 && current->outfile != 0) // last command 
	{
		dup2(current->outfile, STDOUT_FILENO);
		// dup_io(&current->outfile, STDOUT_FILENO);
		close(current->outfile);
	}
	else
		dup2(tmp_fd[1], STDOUT_FILENO);
	if (data->pipe_fd[READ] != -1)
		close (data->pipe_fd[READ]);
	close (tmp_fd[WRITE]);
	return (0);
}

int	update_pipes(int *pipe_fd, int i, int num_cmds, int *tmp_fd)
{
	(void)i;
	if (num_cmds > 1)
	{
		pipe_fd[READ] = tmp_fd[READ];
	}
	return 0;
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

int	open_fds_out(t_exec *current, int command)
{
	int i;
	int j;
	// int cmds;

	(void)command;
	i = 0;
	j = 0;
	// cmds = get_data()->cmd_count;
	while (current->red_out[i])
		i++;
	while (current->red_out[j])
	{
		current->outfile = xopen(current->red_out[j], false);
		if (i != 1 && j != i - 1)
			close(current->outfile);
		j++;
	}
	// if (command == cmds - 1 && current->outfile == 0)
	// 	current->outfile = 1;
	return (0);
}
