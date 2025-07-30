/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:52:37 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/30 10:48:04 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_data(t_data *data);

void	error_env_exp(t_data *data)
{
	clean_data(data);
	clear_history();
	ft_putendl_fd(ERR_MSG_MEM, 2);
	exit(FAILURE);
}

void	error_lst_env(char *key, char *value, t_data *data)
{
	free(key);
	key = NULL;
	free(value);
	value = NULL;
	clean_data(data);
	ft_putendl_fd(ERR_MSG_MEM, 2);
	exit(FAILURE);
}

void	error_synt(t_data *data)
{
	clean_data(data);
	clear_history();
	ft_putendl_fd(ERR_MSG_HERED, 2);
	exit(INV_SYNTAX);
}

void	error_tok(char *input, t_data *data)
{
	free(input);
	input = NULL;
	clean_data(data);
	clear_history();
	ft_putendl_fd(ERR_MSG_MEM, 2);
	exit(FAILURE);
}

// Frees all allocated memory in the data struct.
static void	clean_data(t_data *data)
{
	ft_lst_env_clear(&data->lst_env);
	data->lst_env = NULL;
	ft_lst_tok_clear(&data->lst_tok);
	data->lst_tok = NULL;
}
