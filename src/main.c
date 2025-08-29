/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:40:06 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/29 09:14:38 by bgazur           ###   ########.fr       */
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
		signals_main();
		if (read_input(&input, data) != SUCCESS)
			continue ;
		if (parse_input(input, data) != SUCCESS)
			continue ;
		if (create_heredocs(data) != SUCCESS)
			continue ;
		merger(data);
		execution(data);
		data->cmd_count = 0;
		ft_lst_exec_clear(&data->lst_exec);
	}
	return (SUCCESS);
}

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}
