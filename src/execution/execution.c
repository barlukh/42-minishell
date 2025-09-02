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
	initialize_execution(data, env);
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
				builtin_process(node, i, data, env);
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
	ft_memset(node->fd, -1, sizeof(int) * 2);
	node->infile = -1;
	node->outfile = -1;
	if (i != get_data()->tok_count - 1)
		pipe(node->fd);
	if (node->in_first == true)
	{
		if (open_fds_in(node) == false)
		{

			parent_fds(node);
			return (false);
		}
		if (open_fds_out(node) == false)
			return (false);
	}
	else
	{
		if (open_fds_out(node) == false)
			return (false);
		if (open_fds_in(node) == false)
		{

			parent_fds(node);
			return (false);
		}
	}
	return (true);
}

void	initialize_execution(t_data *data, char **env)
{
	data->tmp_fd = dup(STDIN_FILENO);
	data->pids = ft_calloc(sizeof(pid_t), data->tok_count);
	// data->pids = NULL;
	if (data->pids == NULL)
	{
		safe_close(&data->tmp_fd);
		clean_and_exit(data, env, 127);
	}
	// {
	// 	perror("malloc failed for pids");
	// 	exit(EXIT_FAILURE);
	// }
}

int	child_process(t_exec *node, int i, char **env, t_data *data)
{
	data->pids[i] = fork();
	if (data->pids[i] < 0)
	{
		perror("fork error:");
		exit(EXIT_FAILURE);
	}
	if (data->pids[i] == 0)
	{
		execute_child(node, i, env, data);
	}
	if (get_data()->tok_count > 1)
		parent_fds(node);
	return (0);
}

void	execute_child(t_exec *node, int i, char **env, t_data *data)
{
	char	*path;

	path = NULL;
	signals_exec_child();
	redirections_io(node, i);
	path = path_finder(node->cmd_arg, env);
	path_checker(data, node, env, path);
	if (path && access(path, X_OK) == 0
			&& node->cmd_arg[0] && node->cmd_arg[0][0] != '\0')
	{
		execve(path, node->cmd_arg, env);
		perror(node->cmd_arg[0]);
		exit(EXIT_FAILURE);
	}
	if (access(path, F_OK) == 0 && access(path, X_OK != 0))
	{
		perror(path);
		clean_and_exit(data, env, 126);
	}
	if (access(path, F_OK) != 0)
	{
		ft_putendl_fd2(node->cmd_arg[0], ": No such file or directory", STDERR_FILENO);
		clean_and_exit(data, env, 127);
	}
	ft_putendl_fd2(node->cmd_arg[0], ": command not found", STDERR_FILENO);
	clean_and_exit(data, env, 127);
}
