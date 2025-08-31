
#include "minishell.h"

int	redirections_io(t_exec *node, int i)
{
	int cmds;

	cmds = get_data()->tok_count;
	if (cmds == 1 && node->outfile == 0 && node->infile == 0)
		return (0);

	if (node->infile > 2 )
		safe_dup(&node->infile, STDIN_FILENO);
	else if (i != 0)
		safe_dup(&get_data()->tmp_fd, STDIN_FILENO);
	if (node->outfile > 2)
		safe_dup(&node->outfile, STDOUT_FILENO);
	else if (i != cmds - 1)
		safe_dup(&node->fd[WRITE], STDOUT_FILENO);

	if (node->fd[READ] > 2 )
		safe_close(&node->fd[READ]);
	return (0);
}

int redirections_builtin(t_exec *node, int i)
{
	int cmds;

	cmds = get_data()->tok_count;
	if (node->infile > 2)
		safe_dup(&node->infile, STDIN_FILENO);
	else if (i != 0)
		safe_dup(&get_data()->tmp_fd, STDIN_FILENO);
	if (node->outfile > 2)
		safe_dup(&node->outfile, STDOUT_FILENO);
	else if (i != cmds - 1)
		safe_dup(&node->fd[WRITE], STDOUT_FILENO);
	return (0);
}

void	open_fds_in(bool *err_trig, t_exec *node)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (node->in[i])
		i++;
	while (node->in[j])
	{
		safe_open_in(node, j, err_trig);
		if (i != 1 && j != i - 1)
			close(node->infile);
		j++;
	}
}

bool	open_fds_out(t_exec *node)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (node->out[i])
		i++;
	while (node->out[j])
	{
		if (safe_open_out(node, j) == false)
			return (false);
		if (i != 1 && j != i - 1)
			close(node->outfile);
		j++;
	}
	return (true);
}
