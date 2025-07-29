/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 07:52:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/29 14:42:57 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(char **input)
{
	*input = readline("minishell$ ");
	add_history(*input);
}

bool	parse_input(char *input, t_data *data)
{
	if (tokenizer(input, data) != SUCCESS)
		error_tok(input, data);
	if (syntax_checker(data) != SUCCESS)
	{
		data->exit_status = 2;
		return (FAILURE);
	}
	if (env_expander(data) != SUCCESS)
		error_env_exp(data);
	quote_remover(data);
	return (SUCCESS);
}
