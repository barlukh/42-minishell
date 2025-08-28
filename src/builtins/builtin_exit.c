/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:02:30 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/28 08:58:14 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_without_arg(t_data *data);
static void	check_invalid_numerical(t_exec *current, t_data *data);
static void	exit_atoi_overflow(t_data *data);
static void	exit_with_arg(int exit_number, t_data *data);

bool	builtin_exit(t_exec *current, t_data *data)
{
	int	exit_num;

	if (ft_strcmp(current->cmd_arg[0], "exit") == 0)
	{
		ft_putendl_fd(ERR_MSG_EXIT, STDOUT_FILENO);
		if (!current->cmd_arg[1])
			exit_without_arg(data);
		check_invalid_numerical(current, data);
		if (current->cmd_arg[2])
		{
			ft_putendl_fd(ERR_MSG_EXARG, STDERR_FILENO);
			if (data->exit_status == 0)
				data->exit_status = 1;
			return (true);
		}
		if (current->cmd_arg[1])
		{
			exit_num = ft_atoi(current->cmd_arg[1]);
			if (exit_num == ERROR)
				exit_atoi_overflow(data);
			exit_with_arg(exit_num, data);
		}
	}
	return (false);
}

// Exits with an unmodified exit status.
static void	exit_without_arg(t_data *data)
{
	clean_data(data);
	clear_history();
	exit(data->exit_status);
}

// Checks if the second argument is a numerical value.
static void	check_invalid_numerical(t_exec *current, t_data *data)
{
	size_t	i;

	i = 0;
	if (current->cmd_arg[1])
	{
		if (current->cmd_arg[1][0] == '\0')
		{
			clean_data(data);
			clear_history();
			ft_putendl_fd(ERR_MSG_NUMARG, STDERR_FILENO);
			data->exit_status = 2;
			exit(data->exit_status);
		}
		while (current->cmd_arg[1][i])
		{
			if (!ft_isdigit(current->cmd_arg[1][i++]))
			{
				clean_data(data);
				clear_history();
				ft_putendl_fd(ERR_MSG_NUMARG, STDERR_FILENO);
				data->exit_status = 2;
				exit(data->exit_status);
			}
		}
	}
}

// Handles an exit wwhen ft_atoi overflows.
static void	exit_atoi_overflow(t_data *data)
{
	ft_putendl_fd(ERR_MSG_NUMARG, STDERR_FILENO);
	clean_data(data);
	clear_history();
	data->exit_status = 2;
	exit(data->exit_status);
}

// Exits with an exit status set by the argument.
static void	exit_with_arg(int exit_number, t_data *data)
{
	clean_data(data);
	clear_history();
	data->exit_status = exit_number;
	exit(data->exit_status);
}
