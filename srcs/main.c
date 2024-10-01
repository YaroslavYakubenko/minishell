/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:03:20 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/01 18:49:29 by yyakuben         ###   ########.fr       */
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
	signal(SIGQUIT, SIG_IGN); // Ctrl + '\'
	while (1)
	{
		input = readline("minishell% ");
		if (!input)
		{
			free(input);
			printf("exit\n");
			exit(0);
		}
		env_list = init_new_list(envp);
		if (*input)
			add_history(input);
		expanded_input = expand_and_compress(input, env_list);
		cmd = ft_start_parse(expanded_input, envp);
		ft_give_marks(cmd);
		ft_handle_cmd_mark(cmd);
		ft_start(cmd);
		// free_env_list(env_list);
	}
	rl_clear_history();
	return (0);
}

// if (quotes[0] || quotes[1])
// 	{
// 		printf("Error: syntax error with quotes\n");
// 		free(result);
// 		return (NULL);
// 	}

// < in ls -l | wc -c > out | cat << g | echo "Hello World!" >> out | echo 'Yes $PWD' | echo 'Yes $SHLVL'