/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 07:52:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/07 13:06:34 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	read_input(char **input, t_data *data)
{
	rl_done = 0;
	rl_event_hook = NULL;
	*input = readline("minishell$ ");
	if (!*input)
	{
		ft_lst_env_clear(&data->lst_env);
		clear_history();
		ft_putendl_fd(ERR_MSG_EXIT, STDERR_FILENO);
		exit(data->exit_status);
	}
	if (ft_strlen(*input) > INPUT_MAX)
	{
		data->exit_status = 2;
		ft_putendl_fd(ERR_MSG_INPUT, STDERR_FILENO);
		free(*input);
		return (FAILURE);
	}
	add_history(*input);
	return (SUCCESS);
}

bool	parse_input(char *input, t_data *data)
{
	tokenizer(input, data);
	if (syntax_checker(data) != SUCCESS)
	{
		ft_lst_tok_clear(&data->lst_tok);
		data->exit_status = 2;
		return (FAILURE);
	}
	env_expander(data);
	heredoc_identifier(data);
	quote_remover(data);
	parsing_finalizer(data);
	return (SUCCESS);
}
