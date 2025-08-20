/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 09:18:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/20 09:17:39 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_invalid_option(char *content);
static void	update_exit_status(bool inv_id, t_data *data);

bool	builtin_export(t_exec *current, t_data *data)
{
	bool	inv_id;
	size_t	i;

	inv_id = false;
	i = 1;
	if (ft_strcmp(current->cmd_arg[0], "export") == 0)
	{
		if (current->cmd_arg[i] && is_invalid_option(current->cmd_arg[i]))
		{
			ft_putendl_fd(ERR_MSG_EXPORT, STDERR_FILENO);
			data->exit_status = 2;
			return (true);
		}
		if (current->cmd_arg[i][0] == '-')
			i++;
		while (current->cmd_arg[i])
		{
			export_loop(&inv_id, current->cmd_arg[i], data);
			i++;
		}
		update_exit_status(inv_id, data);
		return (true);
	}
	return (false);
}

// Checks if the argument is an invalid option.
static bool	is_invalid_option(char *content)
{
	if (!content || content[0] != '-')
		return (false);
	if (content[1] == '\0')
		return (false);
	if (content[1] != '-')
		return (true);
	if (content[1] == '-' && content[2] == '\0')
		return (false);
	return (true);
}

// Updates the exit status.
static void	update_exit_status(bool inv_id, t_data *data)
{
	if (inv_id == true)
		data->exit_status = 1;
	else
		data->exit_status = 0;
}
