/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:52:37 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/29 11:27:33 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_env_exp(t_env **lst_env, t_token **lst_tok)
{
	ft_lst_env_clear(lst_env);
	lst_env = NULL;
	ft_lst_tok_clear(lst_tok);
	lst_tok = NULL;
	clear_history();
	ft_putendl_fd(ERR_MSG_MEM, 2);
	return (FAILURE);
}

int	error_lst_env(char *key, char *value, t_env **lst_env)
{
	free(key);
	key = NULL;
	free(value);
	value = NULL;
	ft_lst_env_clear(lst_env);
	lst_env = NULL;
	ft_putendl_fd(ERR_MSG_MEM, 2);
	return (FAILURE);
}

int	error_synt(t_env **lst_env, t_token **lst_tok)
{
	ft_lst_env_clear(lst_env);
	lst_env = NULL;
	ft_lst_tok_clear(lst_tok);
	lst_tok = NULL;
	clear_history();
	return (INV_SYNTAX);
}

int	error_tok(char *input, t_env **lst_env, t_token **lst_tok)
{
	free(input);
	input = NULL;
	ft_lst_env_clear(lst_env);
	lst_env = NULL;
	ft_lst_tok_clear(lst_tok);
	lst_tok = NULL;
	clear_history();
	ft_putendl_fd(ERR_MSG_MEM, 2);
	return (FAILURE);
}
