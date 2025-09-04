/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 09:18:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/09/04 13:17:41 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	print_check(char *arg, t_data *data, t_exec *node);
static bool	print_action(t_env **arr, t_data *data);
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
		if (print_check(current->cmd_arg[1], data, current) == true)
			return (true);
		if (current->cmd_arg[1] && is_invalid_option(current->cmd_arg[1]))
		{
			ft_putendl_fd(ERR_MSG_EXPORT, STDERR_FILENO);
			data->exit_status = 2;
			return (true);
		}
		if (current->cmd_arg[1][0] == '-')
			i++;
		while (current->cmd_arg[i])
		{
			builtin_exp_loop(&inv_id, current->cmd_arg[i], current, data);
			i++;
		}
		return (update_exit_status(inv_id, data));
	}
	return (false);
}

// Checks if the second argument exists prepares the env for printing.
static bool	print_check(char *arg, t_data *data, t_exec *node)
{
	size_t	i;
	t_env	**arr;
	t_env	*current;

	if (!arg)
	{
		i = ft_lst_env_size(data->lst_env);
		arr = ft_calloc(i + 1, sizeof(t_env *));
		if (!arr)
		{
			close_all_fds(data, node);
			error_general_mem(data);
		}
		i = 0;
		current = data->lst_env;
		while (current)
		{
			arr[i++] = current;
			current = current->next;
		}
		arr[i] = NULL;
		ft_lst_env_sort(arr, i);
		return (print_action(arr, data));
	}
	return (false);
}

// Prints sorted env.
static bool	print_action(t_env **arr, t_data *data)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		if (ft_strcmp("_", arr[i]->key) == 0)
		{
			i++;
			continue ;
		}
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (arr[i]->assigned == true)
		{
			ft_putstr_fd(arr[i]->key, STDOUT_FILENO);
			write(STDOUT_FILENO, "=\"", 2);
			ft_putstr_fd(arr[i]->value, STDOUT_FILENO);
			write(STDOUT_FILENO, "\"\n", 2);
		}
		else
			ft_putendl_fd(arr[i]->key, STDOUT_FILENO);
		i++;
	}
	free(arr);
	data->exit_status = 0;
	return (true);
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
