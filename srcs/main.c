/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:03:20 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/05 15:52:27 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->name);
		free(tmp->val);
		free(tmp);
	}
}

int	are_quotes_closed(char *input)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (*input)
	{
		check_quotes(*input, &in_single_quote, &in_double_quote);
		input++;
	}
	return (!(in_single_quote || in_double_quote));
}

void	ft_print_doulbe_pointer(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

void	ft_print_cmd(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd)
	{
		printf("this is the %d command: \n", i);
		printf("cmd_nbr: %d\n", cmd->cmd_nbr);
		printf("pipe_nbr: %d\n", cmd->pipe_nbr);
		printf("before_pipe: %d\n", cmd->before_pipe);
		printf("after_pipe: %d\n", cmd->after_pipe);
		printf("input: %d\n", cmd->input);
		printf("output: %d\n", cmd->output);
		printf("append: %d\n", cmd->append);
		printf("heredoc: %d\n", cmd->heredoc);
		ft_print_doulbe_pointer(cmd->args);
		cmd = cmd->next;
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env_list;
	char	*input;
	char	*expanded_input;

	(void)ac;
	(void)av;
	setup_signals();
	while (1)
	{
		input = get_input();
		env_list = init_new_list(envp);
		if (check_syntax(input))
		{
			free(input);
			continue ;
		}
		expanded_input = expand_and_compress(input, env_list);
		handle_command(expanded_input, envp);
	}
	rl_clear_history();
	return (0);
}
