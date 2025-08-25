
#include "minishell.h"

int	redirections_io(t_exec *node, int i, t_data *data, int *tmp_fd)
{
	int cmds;

	cmds = data->cmd_count;

	// first command
	if (i == 0)
	{
		// with redirections to infile
		if (node->infile > 2 )
			safe_dup(&node->infile, STDIN_FILENO);
	}
	// other commands with redirections to pipe
	else 
		safe_dup(&data->pipe_fd[READ], STDIN_FILENO);

	// last command 
	if (i == cmds - 1)
	{
		// with redirections to outfile
		if (node->outfile > 2)
			safe_dup(&node->outfile, STDOUT_FILENO);
	}
	else
		// other commands with redirections to pipe
		safe_dup(&tmp_fd[1], STDOUT_FILENO);

	//// close
	// if (node->infile != -1)
	// 	safe_close(&node->infile);
	// if (node->outfile != -1)
	// 	safe_close(&node->outfile);
	// if (data->pipe_fd[0] != -1)
	// 	safe_close(&data->pipe_fd[0]);
	// if (data->pipe_fd[1] != -1)
	// 	safe_close(&data->pipe_fd[1]);
	// if (tmp_fd[0] != -1)
	// 	safe_close(&tmp_fd[0]);
	// if (tmp_fd[1] != -1)
	// 	safe_close(&tmp_fd[1]);
	return (0);
}

int	update_pipes(int *pipe_fd, int i, int num_cmds, int *tmp_fd)
{
	(void)i;
	if (num_cmds > 1)
	{
		pipe_fd[READ] = tmp_fd[READ];
		// close(tmp_fd[READ]);
	}
	return 0;
}

int	open_fds_in(t_exec *node)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (node->red_in[i])
		i++;
	while (node->red_in[j])
	{
		node->infile = safe_open(node->red_in[j], true);
		if (i != 1 && j != i - 1)
			close(node->infile);
		j++;
	}
	// if (!node->infile)
	// 	node->infile = -1;
	return (0);
}

int	open_fds_out(t_exec *node, int command)
{
	int i;
	int j;
	// int cmds;

	(void)command;
	i = 0;
	j = 0;
	// cmds = get_data()->cmd_count;
	while (node->red_out[i])
		i++;
	while (node->red_out[j])
	{
		node->outfile = safe_open(node->red_out[j], false);
		if (i != 1 && j != i - 1)
			close(node->outfile);
		j++;
	}
	// if (!node->outfile)
	// 	node->outfile = -1;
	return (0);
}
