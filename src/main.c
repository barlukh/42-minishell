/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:40:06 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/07 11:46:54 by bgazur           ###   ########.fr       */
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
		if (create_heredoc_temps(data) != SUCCESS)
			continue ;
		test_tok(data);
		test_builtins(data);
		ft_lst_tok_clear(&data->lst_tok);
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
	t_token	*current;

	printf("%s\n", "TOKENS:");
	current = data->lst_tok;
	while (current)
	{
		if (current->type == 0)
			printf("%-20s %s\n", "TOK_PIPE", current->content);
		else if (current->type == 1)
			printf("%-20s %s\n", "TOK_IN", current->content);
		else if (current->type == 2)
			printf("%-20s %s\n", "TOK_OUT", current->content);
		else if (current->type == 3)
			printf("%-20s %s\n", "TOK_HERE", current->content);
		else if (current->type == 4)
			printf("%-20s %s\n", "TOK_HERE_QTD", current->content);
		else if (current->type == 5)
			printf("%-20s %s\n", "TOK_HERE_UNQTD", current->content);
		else if (current->type == 6)
			printf("%-20s %s\n", "TOK_APP", current->content);
		else if (current->type == 7)
			printf("%-20s %s\n", "TOK_WORD", current->content);
		else if (current->type == 8)
			printf("%-20s %s\n", "TOK_CMD", current->content);
		else if (current->type == 9)
			printf("%-20s %s\n", "TOK_ARG", current->content);
		current = current->next;
	}
}

// TEST - prints builtins. (REMOVE BEFORE SUBMISSION!)
static void	test_builtins(t_data *data)
{
	int		return_value;
	t_token	*current;

	printf("\n%s\n", "BUILTINS:");
	current = data->lst_tok;
	while (current)
	{
		return_value = builtins_check(&current, data);
		if (current)
			current = current->next;
	}
}
