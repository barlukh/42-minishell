
#include "minishell.h"

int	builtin_process(t_exec *node, int i, char **env, t_data *data);

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
		ft_memset(node->fd, -1, sizeof(int) * 2);
		node->infile = -1;
		node->outfile = -1;
		if (i != get_data()->tok_count - 1)
			pipe(node->fd);
		if (open_fds_in(node) == false)
			return ;
		if (open_fds_out(node) == false)
			return ;
		if (is_builtins(node->cmd_arg) == true)
		{
			builtin_process(node, i, env, data);
			// builtins_check(node, data);
			// safe_close(&data->tmp_fd); //still hangs
		}
		else
			child_process(node, i, env, data);
		node= node->next;
		i++;
	}
	// if (data->tmp_fd > 2 )
	// 	safe_close(&data->tmp_fd);
	wait_process(data->pids, data);
}
\
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

int	builtin_process(t_exec *node, int i, char **env, t_data *data)
{
	(void)env;
	if (get_data()->tok_count > 1)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
		{
			perror("fork error:");
			exit(EXIT_FAILURE);
		}
		if (data->pids[i] == 0)
		{
			redirections_io(node, i);
			builtins_check(node, data);
			exit(0); // check code
		}
		safe_close(&node->fd[WRITE]);
		safe_close(&data->tmp_fd);
		data->tmp_fd = node->fd[READ];
	}
	else
	{
		redirections_io(node, i);
		builtins_check(node, data);
		safe_close(&node->fd[WRITE]);
		safe_close(&data->tmp_fd);
		data->tmp_fd = node->fd[READ];
	}
	return (0);
}

int	child_process(t_exec *node, int i, char **env, t_data *data)
{
	char	*path;

	path = NULL;
	data->pids[i] = fork();
	if (data->pids[i] < 0)
	{
		perror("fork error:");
		exit(EXIT_FAILURE);
	}
	if (data->pids[i] == 0)
	{
		redirections_io(node, i);
		path = path_finder(node->cmd_arg, env);
		if (path && access(path, X_OK) == 0)
		{
			execve(path, node->cmd_arg, env);
			perror(node->cmd_arg[0]);
			exit(EXIT_FAILURE);
		}
		perror(node->cmd_arg[0]);
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
