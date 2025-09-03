/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:13:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/09/03 10:39:26 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_dir(char *is_path, t_exec *node, t_data *data)
{
	if (is_path != NULL)
	{
		ft_putendl_fd2(node->cmd_arg[0], ": Is a directory", STDERR_FILENO);
		clean_and_exit(data, node, 126);
	}
	else if (ft_strcmp(node->cmd_arg[0], ".") == 0)
	{
		ft_putendl_fd(".: filename argument required", STDERR_FILENO);
		ft_putendl_fd(".: usage: . filename [arguments]", STDERR_FILENO);
		clean_and_exit(data, node, 127);
	}
	else
	{
		ft_putendl_fd2(node->cmd_arg[0], ": command not found", STDERR_FILENO);
		clean_and_exit(data, node, 127);
	}
}

void	check_access(char *is_path, t_exec *node, t_data *data)
{
	if (is_path)
	{
		ft_putendl_fd2(node->cmd_arg[0], ": Permission denied", STDERR_FILENO);
		clean_and_exit(data, node, 126);
	}
	else
	{
		ft_putendl_fd2(node->cmd_arg[0], ": command not found", STDERR_FILENO);
		clean_and_exit(data, node, 127);
	}
}

void	check_cmd(t_exec *node, t_data *data)
{
	ft_putendl_fd2(node->cmd_arg[0], ": command not found", STDERR_FILENO);
	clean_and_exit(data, node, 127);
}


void	check_empty(t_exec *node, t_data *data)
{
	ft_putendl_fd2(node->cmd_arg[0], ": command not found", STDERR_FILENO);
	clean_and_exit(data, node, 127);
}
