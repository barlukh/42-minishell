/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:40:06 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/29 09:41:31 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	test_tok(t_token **lst_tok);
static void	test_builtins(t_env **lst_env, t_token **lst_tok);

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_env	*lst_env;
	t_token	*lst_tok;

	(void)argc;
	(void)argv;
	lst_env = NULL;
	lst_tok = NULL;
	create_lst_env(env, &lst_env);
	while (true)
	{
		read_input(&input);
		printf("----------------------------\n");
		parse_input(input, &lst_env, &lst_tok);
		test_tok(&lst_tok);
		test_builtins(&lst_env, &lst_tok);
		ft_lst_tok_clear(&lst_tok);
		printf("----------------------------\n");
	}
	clear_history();
	ft_lst_env_clear(&lst_env);
	return (SUCCESS);
}

// TEST - prints tokens. (REMOVE BEFORE SUBMISSION!)
static void	test_tok(t_token **lst_tok)
{
	t_token	*current;

	printf("%s\n", "TOKENS:");
	current = *lst_tok;
	while (current)
	{
		if (current->type == 0)
			printf("%-14s %s\n", "PIPE", current->content);
		else if (current->type == 1)
			printf("%-14s %s\n", "REDIR_IN", current->content);
		else if (current->type == 2)
			printf("%-14s %s\n", "REDIT_OUT", current->content);
		else if (current->type == 3)
			printf("%-14s %s\n", "REDIR_HEREDOC", current->content);
		else if (current->type == 4)
			printf("%-14s %s\n", "REDIR_APPEND", current->content);
		else if (current->type == 5)
			printf("%-14s %s\n", "WORD", current->content);
		current = current->next;
	}
}

// TEST - prints builtins. (REMOVE BEFORE SUBMISSION!)
static void	test_builtins(t_env **lst_env, t_token **lst_tok)
{
	int		return_value;
	t_token	*current;

	printf("\n%s\n", "BUILTINS:");
	current = *lst_tok;
	while (current)
	{
		return_value = builtins_check(lst_env, &current);
		current = current->next;
	}
}
