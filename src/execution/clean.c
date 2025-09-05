/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:42:13 by edlucca           #+#    #+#             */
/*   Updated: 2025/09/04 16:42:14 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_and_exit(t_data *data, t_exec *node, int exit_code)
{
	ft_lst_env_clear(&get_data()->lst_env);
	get_data()->lst_env = NULL;
	close_all_fds(data, node);
	ft_lst_exec_clear(&data->lst_exec);
	data->lst_exec = NULL;
	ft_free_array(data->env);
	free(data->pids);
	clear_history();
	data->exit_status = exit_code;
	exit(data->exit_status);
}

void	parent_fds(t_exec *node)
{
	if (node->fd[WRITE] > 2)
		safe_close(&node->fd[WRITE]);
	if (get_data()->tmp_fd > 2)
		safe_close(&get_data()->tmp_fd);
	if (node->fd[READ] > 2)
		get_data()->tmp_fd = node->fd[READ];
	if (node->infile > 2)
		safe_close(&node->infile);
	if (node->outfile > 2)
		safe_close(&node->outfile);
}

void	close_all_fds(t_data *data, t_exec *node)
{
	if (node->fd[READ] > 2)
		safe_close(&node->fd[READ]);
	if (node->fd[WRITE] > 2)
		safe_close(&node->fd[WRITE]);
	if (data->tmp_fd > 2)
		safe_close(&data->tmp_fd);
	if (node->infile > 2)
		safe_close(&node->infile);
	if (node->outfile > 2)
		safe_close(&node->outfile);
	restore_fds(node);
}
