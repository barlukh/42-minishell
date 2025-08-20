
#include "minishell.h"

int	dup_io(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		return (-1);
	if (oldfd != newfd)
		close (oldfd);
	return (newfd);
}

int	xopen(const char *pathname, bool is_infile)
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
