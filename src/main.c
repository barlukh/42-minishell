/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:40:06 by bgazur            #+#    #+#             */
/*   Updated: 2025/09/08 17:23:08 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	*data;

	(void)argc;
	(void)argv;
	input = NULL;
	data = get_data();
	create_lst_env(env, data);
	while (true)
	{
		signals_readline();
		if (read_input(&input, data) != SUCCESS)
			continue ;
		if (parse_input(input, data) != SUCCESS)
			continue ;
		if (create_heredocs(data) != SUCCESS)
			continue ;
		merger(data);
		signals_exec_parent();
		execution(data);
		data->tok_count = 0;
		ft_lst_exec_clear(&data->lst_exec);
		data->lst_exec = NULL;
	}
	return (SUCCESS);
}

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}
