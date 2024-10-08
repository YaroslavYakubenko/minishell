/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:03:20 by yyakuben          #+#    #+#             */

/*   Updated: 2024/09/17 17:45:28 by dyao             ###   ########.fr       */

/*   Updated: 2024/09/12 22:37:22 by yyakuben         ###   ########.fr       */

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
	// t_token	**tokens;
	int		i;
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	i = 0;
	signal(SIGINT, sigint_handler); // Ctrl + C
	signal(SIGQUIT, sigquit_handler); // Ctrl + '\'
	env_list = init_new_list(envp);
	while ((input = readline("minishell%")) != NULL)
	{
		if (*input)
			add_history(input);
		if (input == 0)
			eof_handler(); // Ctrl + D
		expanded_input = expand_and_compress(input, env_list);


		cmd = ft_start_parse(expanded_input);
		ft_give_marks(cmd);
		ft_handle_cmd_mark(cmd);
		// ft_print_cmd(cmd);
		ft_start(cmd, envp);





		// tokens = parse_token(expanded_input);
		// if (tokens != NULL)
		// {
		// 	i = 0;
		// 	while (tokens[i])
		// 	{
		// 		printf("Type: %d\t", tokens[i]->type);
		// 		printf("Token: %s\n", tokens[i]->token);
		// 		i++;
		// 	}
		// }
		// if (expanded_input != NULL)
		// {
		// 	printf("expanded: %s\n", expanded_input);
		// 	free(expanded_input);
		// }
		free(input);
	}
	rl_clear_history();
	free_env_list(env_list);
	return (0);
}

// < in ls -l | wc -c > out | cat << g | echo "Hello World!" >> out | echo 'Yes $PWD' | echo 'Yes $SHLVL'