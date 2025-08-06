/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:46:41 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/06 11:08:54 by bgazur           ###   ########.fr       */
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
