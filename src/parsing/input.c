/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 07:52:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/29 11:29:19 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(char **input)
{
	*input = readline("minishell$ ");
	add_history(*input);
}

void	parse_input(char *input, t_env **lst_env, t_token **lst_tok)
{
	if (tokenizer(input, lst_tok) != SUCCESS)
		exit(error_tok(input, lst_env, lst_tok));
	if (syntax_checker(lst_tok) != SUCCESS)
		exit(error_synt(lst_env, lst_tok));
	if (env_expander(lst_env, lst_tok) != SUCCESS)
		exit(error_env_exp(lst_env, lst_tok));
	quote_remover(lst_tok);
}
