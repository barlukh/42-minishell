/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:52:37 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/22 15:53:10 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error_lst_env(t_env **lst_env)
{
	ft_lst_env_clear(lst_env);
	lst_env = NULL;
	ft_putendl_fd("Error allocating memory", 2);
	exit(FAILURE);
}

int	error_tokenizer(char *input, t_token **lst_tok, t_env **lst_env)
{
	free(input);
	input = NULL;
	ft_lst_tok_clear(lst_tok);
	lst_tok = NULL;
	ft_lst_env_clear(lst_env);
	lst_env = NULL;
	clear_history();
	ft_putendl_fd("Error allocating memory", 2);
	exit(FAILURE);
}

int	error_parser(t_token **lst_tok)
{
	ft_lst_tok_clear(lst_tok);
	lst_tok = NULL;
	clear_history();
	ft_putendl_fd("Syntax error", 2);
	exit(ERR_SYNTAX);
}
