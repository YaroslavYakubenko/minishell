/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:03:20 by yyakuben          #+#    #+#             */
/*   Updated: 2024/09/30 17:48:26 by dyao             ###   ########.fr       */
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

int main (int ac, char **av, char **envp)
{
	t_env	*env_list;
	char	*input;
	char	*expanded_input;
	int		i;
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	i = 0;
	signal(SIGINT, sigint_handler); // Ctrl + C
	signal(SIGQUIT, sigquit_handler); // Ctrl + '\'
	signal(SIGTERM, eof_handler); // Ctrl + D
	input = readline("minishell% ");
	while (input != NULL)
	{
		env_list = init_new_list(envp);
		if (*input)
			add_history(input);
		expanded_input = expand_and_compress(input, env_list);
		cmd = ft_start_parse(expanded_input, envp);
		ft_give_marks(cmd);
		ft_handle_cmd_mark(cmd);
		ft_start(cmd, envp);
		input = readline("minishell% ");
	}
	rl_clear_history();
	return (0);
}

// < in ls -l | wc -c > out | cat << g | echo "Hello World!" >> out | echo 'Yes $PWD' | echo 'Yes $SHLVL'