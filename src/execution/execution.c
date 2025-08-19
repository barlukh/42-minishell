
#include "minishell.h"

void	error_msg(char *str);
int		redirections_io(t_exec current, int i);
int		open_fds_in(t_exec current);
int		open_fds_out(t_exec current);
int		xopen(const char *pathname, bool is_infile);
int		update_pipes(int pipe_fd[2][2], int i, int num_cmds);
int		builting_process(t_exec current, int i);
int		child_process(t_exec current, int i, char **env);
int		dup_io(int oldfd, int newfd);
int		node_count(t_env *temp, int count);
char	*path_finder(char **command, char **env);
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
	current->pids = malloc(sizeof(pid_t) * data->cmd_count);  // num_cmds is the number of commands in the pipeline
	if (current->pids == NULL) {
		perror("malloc failed for pids");
		exit(EXIT_FAILURE);
	}
	while (current)
	{
		// ft_memset(current->pids, 0, sizeof(pid_t));
		// open_fds(*current); // inside child or builting
		if (builtins_check(current, data)) // check if cmd is a builting
			builting_process(*current, i);
		else
			child_process(*current, i, env);
		update_pipes(current->pipe_fd, i, data->cmd_count); // update_pipe on parent side
		current= current->next;
		i++;
	}
	wait_process(current->pids, data);
}

bool	wait_process(pid_t *pid, t_data *data)
{
	int		i;
	int		status;
	int		cmds_count;
	pid_t	term_pid;

	i = 0;
	cmds_count = data->cmd_count;
	while (i < cmds_count)
	{
		term_pid = waitpid(*pid, &status, 0);
		if (term_pid == -1)
			return (false);
		if (term_pid == pid[cmds_count - 1] && (WIFEXITED(status)))
			data->exit_status = WEXITSTATUS(status);
		i++;
	}
	return (true);
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

int	builting_process(t_exec current, int i)
{
	redirections_io(current, i); // resets the reclying system of pipes
	return (0);
}

int	child_process(t_exec current, int i, char **env)
{
	char	*path;
	int		previous;

	path = NULL;
	previous = (i + 1) % 2;
	current.pids[i] = fork();
	if (current.pids[i] < 0)
	{
		perror("fork error:");
		exit(EXIT_FAILURE);
	}
	open_fds_in(current);								
	open_fds_out(current);								
	if (current.pids[i] == 0) // child process
	{
		// resets the reclying system of pipes
		redirections_io(current, i); // TODO:
		// solve paths.
		path = path_finder(current.cmd_arg, env); // TODO:
		execve(path, current.cmd_arg, env);
		free(env);
	}
	if (i != 0)
	{
		close(current.pipe_fd[previous][0]);
		close(current.pipe_fd[previous][1]);
	}
	return (0);
}

char	*get_env_value(char **envp)
{
	char	*path;
	char	*command;
	int		i;
	i = 0;
	command = "PATH";
	path = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(command, envp[i], ft_strlen(command)) == 0
				&& envp[i][ft_strlen(command)] == '=')
		{
			path = ft_strchr(envp[i], '=') + 1;
			break ;
		}
	}
	if (!path)
		return (NULL);
	return (path);
}

char	*path_finder(char **command, char **env)
{
	char	*path_env;
	char	**paths;
	char	*full;
	char	*tmp;
	int i = 0;

	if (!command || !command[0])
		return NULL;
	// if the cmd has already the fullpath
	if (access(command[0], X_OK) == 0)
		return (ft_strdup(command[0]));
	path_env = get_env_value(env);
	if (!path_env)
		return NULL;
	paths = ft_split(path_env, ':');
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (ft_free_array(paths), NULL);
		full = ft_strjoin(tmp, command[0]);
		free(tmp);
		if (!full)
			return (ft_free_array(paths), NULL);
		if (access(full, X_OK) == 0)
			return (ft_free_array(paths), full);
		free(full);
		i++;
	}
	ft_free_array(paths);
	return NULL;
}

int	redirections_io(t_exec current, int i) // TODO:
{
	int cmds;
	int actual;
	int previous;

	actual = i % 2;
	previous = (i + 1) % 2;
	cmds = get_data()->cmd_count;
	if (i == 0)
	{
		if (dup_io(current.infile, STDIN_FILENO) < 0)
			return (4);
	}
	else
		if (dup_io(current.pipe_fd[previous][0], STDIN_FILENO) < 0)
			return (4);
	if (i == cmds -1)
	{
		if (dup_io(current.outfile, STDOUT_FILENO) < 0)
			return (4);
	}
	else
		if (dup_io(current.pipe_fd[actual][1], STDOUT_FILENO) < 0)
			return (4);
	if (i != 0)
	{
		close(current.pipe_fd[previous][0]);
		close(current.pipe_fd[previous][1]);
	}
	if (i == cmds -1)
	{
		close(current.pipe_fd[actual][0]);
		close(current.pipe_fd[actual][1]);
	}
	return (0);
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
