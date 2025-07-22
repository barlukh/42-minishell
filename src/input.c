/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 07:52:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/22 15:49:52 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	read_input(char **input)
{
	*input = readline("minishell$ ");
	add_history(*input);
}

void	parse_input(char *input, t_token **lst_tok, t_env **lst_env)
{
	tokenizer(input, lst_tok, lst_env);
	parser(lst_tok, lst_env);
}
