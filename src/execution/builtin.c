
#include "minishell.h"

int	builtin_process(t_exec *node, int i, t_data *data)
{
	if (get_data()->tok_count > 1)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			clean_and_exit(data, node, 127); // possible leak
		if (data->pids[i] == 0)
		{
			if (pipeline_builtin(node, i) == false)
				return (0);
		}
	}
	else
	{
		if (simple_builtin(node, i) == false)
			return (0);
	}
	parent_fds(node);
	return (0);
}

bool	pipeline_builtin(t_exec *node, int i)
{
	node->saved_stdin = dup(STDIN_FILENO);
	node->saved_stdout = dup(STDOUT_FILENO);
	if (node->saved_stdin == -1 || node->saved_stdout == -1)
		return (perror("dup"), -1); // possible leak
	redirections_builtin(node, i);
	if (i != get_data()->tok_count - 1 && node->outfile == -1)
		safe_dup(&node->fd[WRITE], STDOUT_FILENO);
	if (ft_strcmp(node->cmd_arg[0], "exit") != 0)
		builtins_check(node, get_data());
	close_all_fds(get_data(), node);
	close_builtin(node);
	if (ft_strcmp(node->cmd_arg[0], "exit") == 0)
		builtins_check(node, get_data());
	parent_fds(node);
	clean_and_exit(get_data(), node, 0);
	return (true);
}

bool	simple_builtin(t_exec *node, int i)
{
	node->saved_stdin = dup(STDIN_FILENO);
	node->saved_stdout = dup(STDOUT_FILENO);
	if (node->saved_stdin == -1 || node->saved_stdout == -1)
		return (perror("dup"), -1); // possible leak
	(void)i;
	safe_close(&get_data()->tmp_fd);
	if (node->infile > 2)
		safe_dup(&node->infile, STDIN_FILENO);
	if (node->outfile > 2)
		safe_dup(&node->outfile, STDOUT_FILENO);
	// redirections_builtin(node, i);
	if (ft_strcmp(node->cmd_arg[0], "exit") != 0)
		builtins_check(node, get_data());
	close_all_fds(get_data(), node);
	close_builtin(node);
	if (ft_strcmp(node->cmd_arg[0], "exit") == 0)
		builtins_check(node, get_data());
	return (true);
}

void	close_builtin(t_exec *node)
{
	if ((dup2(node->saved_stdin, STDIN_FILENO) == -1)
			|| (dup2(node->saved_stdout, STDOUT_FILENO) == -1))
		return ;
	safe_close(&node->saved_stdin);
	safe_close(&node->saved_stdout);
}
