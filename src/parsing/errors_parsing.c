/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:52:37 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/31 11:48:32 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_general_mem(t_data *data)
{
	clean_data(data);
	clear_history();
	ft_putendl_fd(ERR_MSG_MEM, STDERR_FILENO);
	data->exit_status = 1;
	exit(data->exit_status);
}

void	error_lst_env(char *key, char *value, t_data *data)
{
	free(key);
	key = NULL;
	free(value);
	value = NULL;
	clean_data(data);
	ft_putendl_fd(ERR_MSG_MEM, STDERR_FILENO);
	data->exit_status = 1;
	exit(data->exit_status);
}

void	error_synt(t_data *data)
{
	clean_data(data);
	clear_history();
	ft_putendl_fd(ERR_MSG_HERE, STDERR_FILENO);
	data->exit_status = 2;
	exit(data->exit_status);
}

void	error_tok(char *input, t_data *data)
{
	free(input);
	input = NULL;
	clean_data(data);
	clear_history();
	ft_putendl_fd(ERR_MSG_MEM, STDERR_FILENO);
	data->exit_status = 1;
	exit(data->exit_status);
}

void	clean_merge(t_exec *node, t_data *data)
{
	free(node->app);
	free(node->cmd_arg);
	free(node->in);
	free(node->out);
	free(node);
	error_general_mem(data);
}
