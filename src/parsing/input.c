/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 07:52:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/30 08:17:58 by bgazur           ###   ########.fr       */
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
	tokenizer(input, data);
	if (syntax_checker(data) != SUCCESS)
	{
		ft_lst_tok_clear(&data->lst_tok);
		data->exit_status = 2;
		return (FAILURE);
	}
	env_expander(data);
	quote_remover(data);
	return (SUCCESS);
}
