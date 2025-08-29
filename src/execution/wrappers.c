
#include "minishell.h"

int	safe_dup(int *oldfd, int newfd)
{
	if (dup2(*oldfd, newfd) == -1)
		return (-1);
	close (*oldfd);
	*oldfd = -1;
	return (newfd);
}

bool	safe_open(t_exec *node, bool is_infile)
{
	if (is_infile == true)
	{
		node->infile = open(node->red_in[0], O_RDONLY);
		if (node->infile == -1)
		{
			get_data()->exit_status = 1;
			perror(node->red_in[0]);
			return (false);
		}
	}
	else
	{
		node->outfile = open(node->red_out[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (node->outfile == -1)
		{
			get_data()->exit_status = 1;
			perror(node->red_in[0]);
			return (false);
		}
	}
	return (true);
}

int	safe_close(int *fd)
{
	close(*fd);
	*fd = -1;
	return (*fd);
}
