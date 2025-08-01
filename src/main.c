/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:40:06 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/01 08:14:41 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	test_tok(t_data *data);
static void	test_builtins(t_data *data);

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	data;

	(void)argc;
	(void)argv;
	input = NULL;
	data.exit_status = 0;
	data.lst_env = NULL;
	data.lst_tok = NULL;
	create_lst_env(env, &data);
	while (true)
	{
		if (read_input(&input, &data) != SUCCESS)
			continue ;
		if (parse_input(input, &data) != SUCCESS)
			continue ;
		test_tok(&data);
		test_builtins(&data);
		ft_lst_tok_clear(&data.lst_tok);
	}
	clear_history();
	ft_lst_env_clear(&data.lst_env);
	return (SUCCESS);
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
			printf("%-14s %s\n", "TOK_PIPE", current->content);
		else if (current->type == 1)
			printf("%-14s %s\n", "TOK_IN", current->content);
		else if (current->type == 2)
			printf("%-14s %s\n", "TOK_OUT", current->content);
		else if (current->type == 3)
			printf("%-14s %s\n", "TOK_HERE", current->content);
		else if (current->type == 4)
			printf("%-14s %s\n", "TOK_APP", current->content);
		else if (current->type == 5)
			printf("%-14s %s\n", "TOK_WORD", current->content);
		else if (current->type == 6)
			printf("%-14s %s\n", "TOK_CMD", current->content);
		else if (current->type == 7)
			printf("%-14s %s\n", "TOK_ARG", current->content);
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
		current = current->next;
	}
}
