/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:52:37 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/23 13:18:42 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error_lst_env(char *err, char *key, char *value, t_env **lst_env)
{
	free(key);
	key = NULL;
	free(value);
	value = NULL;
	ft_lst_env_clear(lst_env);
	lst_env = NULL;
	ft_putendl_fd(err, 2);
	exit(FAILURE);
}

int	error_tok(char *err, char *input, t_env **lst_env, t_token **lst_tok)
{
	free(input);
	input = NULL;
	ft_lst_env_clear(lst_env);
	lst_env = NULL;
	ft_lst_tok_clear(lst_tok);
	lst_tok = NULL;
	clear_history();
	ft_putendl_fd(err, 2);
	exit(FAILURE);
}

int	error_parser(char *err, t_env **lst_env, t_token **lst_tok)
{
	ft_lst_env_clear(lst_env);
	lst_env = NULL;
	ft_lst_tok_clear(lst_tok);
	lst_tok = NULL;
	clear_history();
	ft_putendl_fd(err, 2);
	exit(INV_SYNTAX);
}
