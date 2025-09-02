
#include "minishell.h"

int	builtin_process(t_exec *node, int i, t_data *data, char **env)
{
	if (get_data()->tok_count > 1)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			clean_and_exit(data, env, 127); // possible leak
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
	if (close_builtin(saved_stdin, saved_stdout) == false)
		return (false);
	parent_fds(node);
	exit(0); // error code should be handled
}

bool	simple_builtin(t_exec *node, int i)
{

	int saved_stdin = dup(STDIN_FILENO);
	int saved_stdout = dup(STDOUT_FILENO);

	if (saved_stdin == -1 || saved_stdout == -1)
		return (perror("dup"), -1);
	redirections_builtin(node, i);
	builtins_check(node, get_data());
	if (i != get_data()->tok_count - 1 && node->outfile == -1)
		safe_dup(&node->fd[WRITE], STDOUT_FILENO);
	if (close_builtin(saved_stdin, saved_stdout) == false)
		return (false);
	return (true);
}

bool	close_builtin(int saved_stdin, int saved_stdout)
{
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		return (false);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		return (false);
	close(saved_stdin);
	close(saved_stdout);
	return (true);
}
