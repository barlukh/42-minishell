/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:52:37 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/27 12:15:33 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_lst_env(int err, char *key, char *value, t_env **lst_env)
{
	free(key);
	key = NULL;
	free(value);
	value = NULL;
	ft_lst_env_clear(lst_env);
	lst_env = NULL;
	ft_putendl_fd(ERR_MSG_ENV, 2);
	exit(err);
}

int	error_tok(int err, char *input, t_env **lst_env, t_token **lst_tok)
{
	free(input);
	input = NULL;
	ft_lst_env_clear(lst_env);
	lst_env = NULL;
	ft_lst_tok_clear(lst_tok);
	lst_tok = NULL;
	clear_history();
	ft_putendl_fd(ERR_MSG_MEM, 2);
	exit(err);
}

int	error_par(int err, t_env **lst_env, t_token **lst_tok)
{
	ft_lst_env_clear(lst_env);
	lst_env = NULL;
	ft_lst_tok_clear(lst_tok);
	lst_tok = NULL;
	clear_history();
	if (err == FAILURE)
		ft_putendl_fd(ERR_MSG_MEM, 2);
	else if (err == INV_SYNTAX)
		ft_putendl_fd(ERR_MSG_SYN, 2);
	exit(err);
}
