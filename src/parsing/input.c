/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 07:52:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/01 19:54:04 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	read_input(char **input, t_data *data)
{
	*input = readline("minishell$ ");
	if (!*input)
	{
		data->exit_status = 2;
		ft_putendl_fd(ERR_MSG_INNUL, 2);
		return (FAILURE);
	}
	if (ft_strlen(*input) > INPUT_MAX)
	{
		data->exit_status = 2;
		ft_putendl_fd(ERR_MSG_INLEN, 2);
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
	quote_remover(data);
	parsing_finalizer(data);
	return (SUCCESS);
}
