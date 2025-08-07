/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:46:41 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/07 16:13:34 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_heredoc_mem(t_data *data)
{
	clean_data(data);
	clear_history();
	ft_putendl_fd(ERR_MSG_MEM, 2);
	data->exit_status = 1;
	exit(data->exit_status);
}

void	error_heredoc_file(t_data *data)
{
	clean_data(data);
	clear_history();
	ft_putendl_fd(ERR_MSG_FILE, 2);
	data->exit_status = 1;
	exit(data->exit_status);
}

bool	error_heredoc_signal(t_data *data)
{
	(void)data;
	ft_lst_tok_clear(&data->lst_tok);
	return (FAILURE);
}

void	error_heredoc_exp(char *input, int *fd, t_data *data)
{
	free(input);
	close(*fd);
	clean_data(data);
	clear_history();
	ft_putendl_fd(ERR_MSG_MEM, 2);
	data->exit_status = 1;
	exit(data->exit_status);
}
