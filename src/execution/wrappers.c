
#include "minishell.h"

int	safe_dup(int *oldfd, int newfd)
{
	if (dup2(*oldfd, newfd) == -1)
		return (-1);
	// if (oldfd != newfd)
	close (*oldfd);
	*oldfd = -1;
	return (newfd);
}

// void safe_dup(int fd1, int fd2)
// {
// 	if (fd1 == fd2 || fd1 == -1)
// 		return;
// 	if (dup2(fd1, fd2) == -1)
// 	{
// 		perror("dup2 failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	close(fd1);
// }

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
