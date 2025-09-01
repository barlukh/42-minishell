
#include "minishell.h"

static bool	is_out_append(char *out_file);

int	safe_dup(int *oldfd, int newfd)
{
	if (dup2(*oldfd, newfd) == -1)
		return (-1);
	close (*oldfd);
	*oldfd = -1;
	return (newfd);
}

bool	safe_open_in(t_exec *node, int j)
{
	node->infile = open(node->in[j], O_RDONLY);
	if (node->infile == -1)
	{
		perror(node->in[j]);
		get_data()->exit_status = 1;
		return (false);
	}
	return (true);
}

bool	safe_open_out(t_exec *node, int j)
{
	if (is_out_append(node->out[j]))
	{
		node->outfile = open(node->out[j], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (node->outfile == -1)
		{
			get_data()->exit_status = 1;
			perror(node->out[j]);
			return (false);
		}
	}
	else
	{
		node->outfile = open(node->out[j], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (node->outfile == -1)
		{
			get_data()->exit_status = 1;
			perror(node->out[j]);
			return (false);
		}
	}
	return (true);
}

// Checks if an out file is an append file.
static bool	is_out_append(char *out_file)
{
	char	**app_arr;
	size_t	i;

	app_arr = get_data()->lst_exec->app;
	i = 0;
	while (app_arr[i])
	{
		if (ft_strcmp(app_arr[i], out_file) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	safe_close(int *fd)
{
	close(*fd);
	*fd = -1;
	return (*fd);
}
