/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 07:52:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/26 15:53:49 by bgazur           ###   ########.fr       */
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
		exit(error_tok(FAILURE, input, lst_env, lst_tok));
	if (syntax_checker(lst_tok) != SUCCESS)
		exit(error_par(INV_SYNTAX, lst_env, lst_tok));
	if (env_expander(lst_env, lst_tok) != SUCCESS)
		exit(error_par(FAILURE, lst_env, lst_tok));
	quote_remover(lst_tok);
}
