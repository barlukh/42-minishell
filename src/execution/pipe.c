
#include "minishell.h"

int	redirections_io(t_exec *node, int i)
{
	int cmds;

	cmds = get_data()->cmd_count;
	// first command
	if (cmds == 1 && node->outfile == 0)
		return (0);

	if (i == 0)
	{
		// with redirections to infile
		if (node->infile > 2 )
			safe_dup(&node->infile, STDIN_FILENO);
	}
	// otherwise read from STDIN
	else
		safe_dup(&get_data()->tmp_fd, STDIN_FILENO);

	// // inner commands
	// if (i != cmds - 1)
	// {
	// 	if (node->outfile > 2)
	// 	safe_dup(&node->outfile, STDOUT_FILENO);
	// }
	// else 
	// 	// other commands with redirections to pipe
	// 	safe_dup(&node->fd[WRITE], STDOUT_FILENO);

	// last command 
	if (node->outfile > 2)
	{
		// with redirections to outfile
		safe_dup(&node->outfile, STDOUT_FILENO);
	}
	else
		// other commands with redirections to pipe
		safe_dup(&node->fd[WRITE], STDOUT_FILENO);

	// close
	if (node->fd[READ] > 2 )
		safe_close(&node->fd[READ]);
	return (0);
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
	return (0);
}

int	open_fds_out(t_exec *node)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (node->red_out[i])
		i++;
	while (node->red_out[j])
	{
		node->outfile = safe_open(node->red_out[j], false);
		if (i != 1 && j != i - 1)
			close(node->outfile);
		j++;
	}
	return (0);
}
