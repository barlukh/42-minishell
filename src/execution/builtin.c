
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
	int saved_stdin;
	int saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (perror("dup"), -1); // possible leak
	redirections_builtin(node, i);
	builtins_check(node, get_data()); // what if builting fail how return the correct code
	if (i != get_data()->tok_count - 1 && node->outfile == -1)
		safe_dup(&node->fd[WRITE], STDOUT_FILENO);
	if (close_builtin(&saved_stdin, &saved_stdout) == false)
		return (false);
	parent_fds(node);
	clean_and_exit(get_data(), node, 0);
	return (true);
}

bool	simple_builtin(t_exec *node, int i)
{

	int saved_stdin;
	int saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (perror("dup"), -1); // possible leak
	// (void)i;
	// safe_close(&get_data()->tmp_fd);
	// if (node->infile > 2)
	// 	safe_dup(&node->infile, STDIN_FILENO);
	// if (node->outfile > 2)
	// 	safe_dup(&node->outfile, STDOUT_FILENO);
	redirections_builtin(node, i);
	builtins_check(node, get_data());
	close_all_fds(get_data(), node);
	if (close_builtin(&saved_stdin, &saved_stdout) == false)
		return (false);
	return (true);
}

bool	close_builtin(int *saved_stdin, int *saved_stdout)
{
	if ((dup2(*saved_stdin, STDIN_FILENO) == -1)
			|| (dup2(*saved_stdout, STDOUT_FILENO) == -1))
		return (false);
	safe_close(saved_stdin);
	safe_close(saved_stdout);
	return (true);
}
