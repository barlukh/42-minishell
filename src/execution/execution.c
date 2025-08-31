#include <sys/stat.h>
#include "minishell.h"

void	execution(t_data *data)
{
	int			i;
	char		**env;
	t_exec		*node;

	i = 0;
	node = data->lst_exec;
	if (!node)
		return ;
	env = rebuild_env(data);
	initialize_execution(data);
	while (node)
	{
		if (open_fds(node, i) == false)
		{
			i++;
			node= node->next;
			continue ;
		}
		if (node->cmd_arg[0])
		{
			if (is_builtins(node->cmd_arg) == true)
				builtin_process(node, i, data);
			else
				child_process(node, i, env, data);
		}
		node= node->next;
		i++;
	}
	wait_process(data->pids, data);
}

bool	open_fds(t_exec *node, int i)
{
	bool	err_trig;

	err_trig = false;
	ft_memset(node->fd, -1, sizeof(int) * 2);
	node->infile = -1;
	node->outfile = -1;
	if (i != get_data()->tok_count - 1)
		pipe(node->fd);
	open_fds_in(&err_trig, node);
	if (err_trig == true)
		return (false);
	if (open_fds_out(node) == false)
		return (false);
	return (true);
}

void	initialize_execution(t_data *data)
{
	data->tmp_fd = dup(STDIN_FILENO);
	data->pids = ft_calloc(sizeof(pid_t), data->tok_count);
	if (data->pids == NULL)
	{
		perror("malloc failed for pids");
		exit(EXIT_FAILURE);
	}
}

int	child_process(t_exec *node, int i, char **env, t_data *data)
{
	char	*path;
	struct	stat sb;

	path = NULL;
	data->pids[i] = fork();
	if (data->pids[i] < 0)
	{
		perror("fork error:");
		exit(EXIT_FAILURE);
	}
	if (data->pids[i] == 0)
	{
		signals_exec_child();
		redirections_io(node, i);
		path = path_finder(node->cmd_arg, env);
		if (ft_strcmp(node->cmd_arg[0], ".") == 0)
		{
			ft_putendl_fd(".: filename argument required", STDERR_FILENO);
			ft_putendl_fd(".: usage: . filename [arguments]", STDERR_FILENO);
			free(env);
			exit(2);
		}
		if ((node->cmd_arg[0] && node->cmd_arg[0][0] != '\0') && 
			stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		{
			ft_putendl_fd2(node->cmd_arg[0], ": Is a directory", STDERR_FILENO);
			free(env);
			exit(126);
		}
		if (path && access(path, X_OK) == 0
				&& node->cmd_arg[0] && node->cmd_arg[0][0] != '\0')
		{
			execve(path, node->cmd_arg, env);
			perror(node->cmd_arg[0]);
			exit(EXIT_FAILURE);
		}
		ft_putendl_fd2(node->cmd_arg[0], ": command not found", STDERR_FILENO);
		free(env);
		exit(127);
	}
	if (get_data()->tok_count > 1)
	{
		safe_close(&node->fd[WRITE]);
		safe_close(&data->tmp_fd);
		data->tmp_fd = node->fd[READ];
	}
	return (0);
}
