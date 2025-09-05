/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:35:57 by edlucca           #+#    #+#             */
/*   Updated: 2025/09/05 19:06:47 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	pipeline_builtin(t_exec *node, int i);
static bool	simple_builtin(t_exec *node, int i);

int	builtin_process(t_exec *node, int i, t_data *data)
{
	if (get_data()->tok_count > 1)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			clean_and_exit(data, node, 127);
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

// Runs the builtin on a pipeline
static bool	pipeline_builtin(t_exec *node, int i)
{
	t_data	*data;

	data = get_data();
	node->saved_stdin = dup(STDIN_FILENO);
	node->saved_stdout = dup(STDOUT_FILENO);
	if (node->saved_stdin == -1 || node->saved_stdout == -1)
	{
		ft_putendl_fd(ERR_MSG_DUP, STDERR_FILENO);
		clean_and_exit(data, node, 1);
	}
	redirections_builtin(node, i);
	if (ft_strcmp(node->cmd_arg[0], "exit") != 0)
		builtins_check(node, get_data());
	if (i != get_data()->tok_count - 1 && node->outfile == -1)
		safe_dup(&node->fd[WRITE], STDOUT_FILENO);
	close_all_fds(get_data(), node);
	restore_fds(node);
	if (ft_strcmp(node->cmd_arg[0], "exit") == 0)
		builtins_check(node, get_data());
	parent_fds(node);
	clean_and_exit(get_data(), node, 0);
	return (true);
}

// Runs the builtin as a single command 
static bool	simple_builtin(t_exec *node, int i)
{
	node->saved_stdin = dup(STDIN_FILENO);
	node->saved_stdout = dup(STDOUT_FILENO);
	if (node->saved_stdin == -1 || node->saved_stdout == -1)
	{
		ft_putendl_fd(ERR_MSG_DUP, STDERR_FILENO);
		clean_and_exit(get_data(), node, 1);
	}
	(void)i;
	safe_close(&get_data()->tmp_fd);
	if (node->infile > 2)
		safe_dup(&node->infile, STDIN_FILENO);
	if (node->outfile > 2)
		safe_dup(&node->outfile, STDOUT_FILENO);
	if (ft_strcmp(node->cmd_arg[0], "exit") != 0)
		builtins_check(node, get_data());
	close_all_fds(get_data(), node);
	restore_fds(node);
	if (ft_strcmp(node->cmd_arg[0], "exit") == 0)
		builtins_check(node, get_data());
	return (true);
}

void	restore_fds(t_exec *node)
{
	if (node->saved_stdin > 2)
	{
		if ((dup2(node->saved_stdin, STDIN_FILENO) == -1))
		{
			ft_putendl_fd(ERR_MSG_DUP, STDERR_FILENO);
			clean_and_exit(get_data(), node, 1);
		}
		safe_close(&node->saved_stdin);
	}
	if (node->saved_stdout > 2)
	{
		if ((dup2(node->saved_stdout, STDOUT_FILENO) == -1))
		{
			ft_putendl_fd(ERR_MSG_DUP, STDERR_FILENO);
			clean_and_exit(get_data(), node, 1);
		}
		safe_close(&node->saved_stdout);
	}
}
