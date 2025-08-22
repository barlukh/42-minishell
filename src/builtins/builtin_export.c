/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 09:18:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/22 11:39:00 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	print_check(char *arg, t_data *data);
static bool	is_invalid_option(char *content);
static bool	update_exit_status(bool inv_id, t_data *data);

bool	builtin_export(t_exec *current, t_data *data)
{
	bool	inv_id;
	size_t	i;

	inv_id = false;
	i = 1;
	if (ft_strcmp(current->cmd_arg[0], "export") == 0)
	{
		if (print_check(current->cmd_arg[1], data) == true)
			return (true);
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
			builtin_export_loop(&inv_id, current->cmd_arg[i], data);
			i++;
		}
		return (update_exit_status(inv_id, data));
	}
	return (false);
}

// Check if the second argument exists and prints export if it doesn't.
static bool	print_check(char *arg, t_data *data)
{
	t_env	*current;

	if (!arg)
	{
		current = data->lst_env;
		while (current)
		{
			ft_putstr_fd(current->key, STDOUT_FILENO);
			write(STDOUT_FILENO, "=", 1);
			ft_putendl_fd(current->value, STDOUT_FILENO);
			current = current->next;
		}
		data->exit_status = 0;		
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

// Updates the exit status and returns true.
static bool	update_exit_status(bool inv_id, t_data *data)
{
	if (inv_id == true)
		data->exit_status = 1;
	else
		data->exit_status = 0;
	return (true);
}
