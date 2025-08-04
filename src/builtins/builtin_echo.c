/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:27:45 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/04 17:59:18 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_n_option(int *passed_n_option, t_token **current);
static void	output_argument(int *passed_word, t_token **current);
static void	end_line(int passed_n_option);

int	builtin_echo(t_token **current)
{
	int	passed_n_option;
	int	passed_word;

	if (ft_strcmp((*current)->content, "echo") == 0)
	{
		passed_n_option = false;
		passed_word = false;
		*current = (*current)->next;
		while (*current && (*current)->type != TOK_PIPE)
		{
			if (ft_strcmp((*current)->content, "-n") == 0
				&& passed_n_option == false && passed_word == false)
			{
				skip_n_option(&passed_n_option, current);
				continue ;
			}
			else if ((*current)->type == TOK_ARG)
				output_argument(&passed_word, current);
			*current = (*current)->next;
		}
		end_line(passed_n_option);
		get_data()->exit_status = 0;
		return (BUILT_YES);
	}
	return (BUILT_NO);
}

// Skips all repeating -n options.
static void	skip_n_option(int *passed_n_option, t_token **current)
{
	*passed_n_option = true;
	while (ft_strcmp((*current)->content, "-n") == 0
		|| (*current)->type != TOK_ARG)
		*current = (*current)->next;
}

// Outputs an argument into STDOUT.
static void	output_argument(int *passed_word, t_token **current)
{
	if (*passed_word == true)
		write(STDOUT_FILENO, " ", 1);
	*passed_word = true;
	ft_putstr_fd((*current)->content, STDOUT_FILENO);
}

// Inserts a newline symbol where applicable.
static void	end_line(int passed_n_option)
{
	if (passed_n_option == false)
		write(STDOUT_FILENO, "\n", 1);
}
