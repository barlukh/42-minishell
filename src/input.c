/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 07:52:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/23 13:18:18 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	read_input(char **input)
{
	*input = readline("minishell$ ");
	add_history(*input);
}

void	parse_input(char *input, t_env **lst_env, t_token **lst_tok)
{
	if (tokenizer(input, lst_tok) != SUCCESS)
		exit(error_tok(ERR_MSG_MEM, input, lst_env, lst_tok));
	if (parser(lst_env, lst_tok) != SUCCESS)
		exit(error_parser(ERR_MSG_SYN, lst_env, lst_tok));
}
