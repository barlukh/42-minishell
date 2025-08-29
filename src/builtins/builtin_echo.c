/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:27:45 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/28 16:33:54 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_n_option(char *content);
static void	skip_n_option(int *passed_n_option, size_t *i, t_exec *current);
static void	output_argument(int *passed_word, size_t i, t_exec *current);
static void	end_line(int passed_n_option, t_data *data);

bool	builtin_echo(t_exec *current, t_data *data)
{
	int		passed_n_option;
	int		passed_word;
	size_t	i;

	i = 0;
	if (ft_strcmp(current->cmd_arg[i++], "echo") == 0)
	{
		passed_n_option = false;
		passed_word = false;
		while (current->cmd_arg[i])
		{
			if (is_valid_n_option(current->cmd_arg[i])
				&& passed_n_option == false && passed_word == false)
			{
				skip_n_option(&passed_n_option, &i, current);
				continue ;
			}
			else
				output_argument(&passed_word, i, current);
			i++;
		}
		end_line(passed_n_option, data);
		return (true);
	}
	return (false);
}

// Checks if the token is a valid -n option.
static bool	is_valid_n_option(char *content)
{
	size_t	i;

	i = 0;
	if (content[i] == '-')
	{
		i++;
		if (content[i] == '\0')
			return (false);
		while (content[i])
		{
			if (content[i] != 'n')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

// Skips all repeating -n options.
static void	skip_n_option(int *passed_n_option, size_t *i, t_exec *current)
{
	*passed_n_option = true;
	while (current->cmd_arg[*i] && (is_valid_n_option(current->cmd_arg[*i])))
		(*i)++;
}

// Outputs an argument into STDOUT.
static void	output_argument(int *passed_word, size_t i, t_exec *current)
{
	if (*passed_word == true)
		write(STDOUT_FILENO, " ", 1);
	*passed_word = true;
	ft_putstr_fd(current->cmd_arg[i], STDOUT_FILENO);
}

// Inserts a newline symbol where applicable and updates the exit status.
static void	end_line(int passed_n_option, t_data *data)
{
	if (passed_n_option == false)
		write(STDOUT_FILENO, "\n", 1);
	data->exit_status = 0;
}
