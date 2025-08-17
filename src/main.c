/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:40:06 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/15 15:21:21 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void		test_tok(t_data *data);
static void		test_builtins(t_data *data);

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
		// execution(data);
		test_tok(data);
		test_builtins(data);
		ft_lst_exec_clear(&data->lst_exec);
	}
	clear_history();
	ft_lst_env_clear(&data->lst_env);
	return (SUCCESS);
}

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

// TEST - prints tokens. (REMOVE BEFORE SUBMISSION!)
static void	test_tok(t_data *data)
{
	size_t	i;
	t_exec	*current_exec;

	printf("\n%s\n", "ARRAYS:");
	current_exec = data->lst_exec;
	while (current_exec)
	{
		i = 0;
		printf("%-20s", "cmd_arg:");
		while (current_exec->cmd_arg[i])
		{
			printf("%s", current_exec->cmd_arg[i]);
			if (current_exec->cmd_arg[i + 1] != NULL)
				printf(" ");
			i++;
		}
		printf("\n");
		i = 0;
		printf("%-20s", "red_in:");
		while (current_exec->red_in[i])
		{
			printf("%s", current_exec->red_in[i]);
			if (current_exec->red_in[i + 1] != NULL)
				printf(" ");
			i++;
		}
		printf("\n");
		i = 0;
		printf("%-20s", "red_out:");
		while (current_exec->red_out[i])
		{
			printf("%s", current_exec->red_out[i]);
			if (current_exec->red_out[i + 1] != NULL)
				printf(" ");
			i++;
		}
		printf("\n%s\n", "-------");
		current_exec = current_exec->next;
	}
}

// TEST - prints builtins. (REMOVE BEFORE SUBMISSION!)
static void	test_builtins(t_data *data)
{
	int		return_value;
	t_token	*current;

	(void)return_value;
	printf("\n%s\n", "BUILTINS:");
	current = data->lst_tok;
	while (current)
	{
		if (current->type == TOK_CMD)
			return_value = builtins_check(&current, data);
		if (current)
			current = current->next;
	}
}
