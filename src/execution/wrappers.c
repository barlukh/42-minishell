
#include "minishell.h"

int	safe_dup(int *oldfd, int newfd)
{
	if (dup2(*oldfd, newfd) == -1)
		return (-1);
	close (*oldfd);
	*oldfd = -1;
	return (newfd);
}

int	safe_open(const char *pathname, bool is_infile)
{
	int fd;

	if (is_infile == true)
	{
		fd = open(pathname, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("open failed", 2);
			exit(3);
		}
	}
	else
	{
		fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("open failed", 2);
			exit(3);
		}
	}
	return fd;
}

int	safe_close(int *fd)
{
	close(*fd);
	*fd = -1;
	return (*fd);
}
