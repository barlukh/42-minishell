/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:46:41 by bgazur            #+#    #+#             */
/*   Updated: 2025/09/08 17:13:24 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_heredoc_mem(t_data *data)
{
	clean_data(data);
	clear_history();
	ft_putendl_fd(ERR_MSG_MEM, STDERR_FILENO);
	data->exit_status = 1;
	exit(data->exit_status);
}

void	error_heredoc_file(t_data *data)
{
	clean_data(data);
	clear_history();
	ft_putendl_fd(ERR_MSG_FILE, STDERR_FILENO);
	data->exit_status = 1;
	exit(data->exit_status);
}

bool	error_heredoc_signal(t_data *data)
{
	ft_lst_tok_clear(&data->lst_tok);
	data->lst_tok = NULL;
	return (FAILURE);
}

void	error_heredoc_exp(char *input, int *fd, t_data *data)
{
	free(input);
	input = NULL;
	close(*fd);
	clean_data(data);
	clear_history();
	ft_putendl_fd(ERR_MSG_MEM, STDERR_FILENO);
	data->exit_status = 1;
	exit(data->exit_status);
}
