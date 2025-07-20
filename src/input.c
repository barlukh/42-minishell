/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 07:52:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/20 15:23:08 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	read_input(char **input)
{
	*input = readline("minishell$ ");
}

void	parse_input(char *input, t_token **lst)
{
	tokenizer(input, lst);
}
