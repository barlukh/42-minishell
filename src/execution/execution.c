
// #include "../include/minishell.h"

// typedef struct s_exec
// {
// 	char            **cmd_arg;
// 	char            **fd_in;
// 	char            **fd_out;
// 	bool            pipe;
// 	struct s_exec    *next;
// }    t_exec;

// void	error_msg(char *str);
// void	open_fds(t_exec current);
// int		xopen(const char *pathname);
// int		update_pipes(t_exec current);
// void	builting_process(t_exec current);
// void	child_process(t_exec current);

// void execution(t_data *data)
// {
// 	size_t i;
// 	t_exec    *current;
// 	int pipe_fd[2][2];

// 	current = data->lst_exec;
// 	while (current)
// 	{
// 		open_fds(*current); // inside child or builting
// 		if (is_bulting(current->cmd_arg)) // check if cmd is a builting
// 			builting_process(*current);
// 		else
// 			child_process(*current);
// 	}
// 	wait_process();
// }

// void	builting_process(t_exec current)
// {
// 	update_pipes(current);
// }

// void	child_process(t_exec current)
// {
// 	update_pipes(current); // resets the reclying system of pipes

// }

// int	update_pipes(t_exec current)
// {
// 	int	curr_fd;
// 	int	prev_fd;

// 	curr_fd = i % 2;
// 	prev_fd = (i + 1) % 2;

// }

// void	open_fds(t_exec current)
// {
// 	int i;

// 	i = 0;
// 	while (current.fd_in[i])
// 	{
// 		current.fd_in = xopen(current.fd_in[i]); // open return int, fd_in is of type char **
// 		i++;
// 	}
// 	i = 0;
// 	while (current.fd_out[i])
// 	{
// 		current.fd_out = xopen(current.fd_out[i]); // open return int, fd_in is of type char **

// 		i++;
// 	}
// }

// int	xopen(const char *pathname)
// {
// 	int fd;

// 	fd = open(pathname, O_RDONLY);
// 	if (fd == -1) {
// 		error_msg("open failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	return fd;
// }

// void	error_msg(char *str)
// {
// 	perror(str);
// }

// // dup2 (fd_in);
// // dup2 (fd_out);
// //
// // execve(data->cmd_arg, PATH, data->lst_env)


