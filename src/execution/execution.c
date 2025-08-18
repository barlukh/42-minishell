
#include "minishell.h"

void	error_msg(char *str);
int		redirections_io(t_exec current);
int		open_fds_in(t_exec current);
int		open_fds_out(t_exec current);
int		xopen(const char *pathname, bool is_infile);
int		update_pipes(int pipe_fd[2][2], int i, int num_cmds);
int		builting_process(t_exec current);
int		child_process(t_exec current);
int		dup_io(int oldfd, int newfd);
int		node_count(t_env *temp, int count);
char	*path_finder(char **command);
char	**rebuild_env(t_env lst_env, int i, int count);
bool	wait_process(pid_t *pid, t_data *data);

void	execution(t_data *data)
{
	t_exec		*current;
	int			i;
	char		**env;

	i = 0;
	current = data->lst_exec;
	// Rebuild env from struct for execve
	env = rebuild_env(*data->lst_env, i, i);
	while (current)
	{
		// open_fds(*current); // inside child or builting
		if (builtins_check(current, data)) // check if cmd is a builting
			builting_process(*current);
		else
			child_process(*current);
		update_pipes(current->pipe_fd, i, data->cmd_count); // update_pipe on parent side
		current= data->lst_exec->next;
		i++;
	}
	// wait_process();
}

int	node_count(t_env *temp, int count)
{
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

char	**rebuild_env(t_env lst_env, int i, int count)
{
	t_env	*temp;
	char	**env_array;
	char	*key_eq;

	temp = &lst_env;
	key_eq = NULL;
	count = node_count(temp, i);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return NULL;
	temp = &lst_env;
	while (temp)
	{
		key_eq = ft_strjoin(temp->key, "=");
		if (!key_eq)
			return NULL;
		env_array[i] = ft_strjoin(key_eq, temp->value);
		free(key_eq);
		if (!env_array[i])
			return NULL;
		i++;
		temp = temp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

int	builting_process(t_exec current)
{
	redirections_io(current); // resets the reclying system of pipes
	return (0);
}

int	child_process(t_exec current)
{
	pid_t	pids;
	char	*path;
	char	**env;

	path = NULL;
	pids = fork();
	if (pids < 0)
	{
		perror("fork error:");
		exit(EXIT_FAILURE);
	}
	if (pids == 0) // child process
	{
		// resets the reclying system of pipes
		redirections_io(current);
		// solve paths.
		path = path_finder(current.cmd_arg);
		execve(path, current.cmd_arg, env);
	}
	return (0);
}

char	*path_finder(char **command)
{
	// if the cmd has already the fullpath
	if (check_access(command[0]) == true) // TODO:
		return (ft_strdup(command[0]));
}

int	redirections_io(t_exec current)
{

}

int	dup_io(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		close (oldfd);
		return (-1);
	}
	if (oldfd != newfd)
		close (oldfd);
	return (newfd);
}

int	update_pipes(int pipe_fd[2][2], int i, int num_cmds)
{
	int current;
	int previous;

	current = i % 2;
	previous = (i + 1) % 2;
	if (i != num_cmds - 1)
	{
		if (pipe(pipe_fd[current]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	if (i != 0)
	{
		close(pipe_fd[previous][0]);
		close(pipe_fd[previous][1]);
	}
	return (0);
}

int	open_fds_in(t_exec current)
{
	int i;

	i = 0;
	while (current.red_in[i])
	{
		current.infile = xopen(current.red_in[i], true); // open return int, red_in is of type char **
		i++;
	}
	return (0);
}

int	open_fds_out(t_exec current)
{
	int i;

	i = 0;
	while (current.red_out[i])
	{
		current.outfile = xopen(current.red_out[i], false); // open return int, red_in is of type char **
		i++;
	}
	return (0);
}

int	xopen(const char *pathname, bool is_infile)
{
	int fd;

	if (is_infile == true)
	{
		fd = open(pathname, O_RDONLY);
		if (fd == -1)
		{
			error_msg("open failed");
			exit(3);
		}
	}
	else
	{
		fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			error_msg("open failed");
			exit(3);
		}
	}
	return fd;
}
