/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:03:20 by yyakuben          #+#    #+#             */
/*   Updated: 2024/08/23 12:03:21 by yyakuben         ###   ########.fr       */
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
	t_token	**tokens;
	int		i;
	
	(void)ac;
	(void)av;
	i = 0;
	env_list = init_new_list(envp);
	while ((input = readline("minishell%")) != NULL)
	{
		if (*input)
			add_history(input);
		tokens = parse_token(input);
		if (tokens != NULL)
		{
			i = 0;
			while (tokens[i])
			{
				printf("Type: %d\n", tokens[i]->type);
				printf("Token: %s\n", tokens[i]->token);
				i++;
			}

		}
		expanded_input = expand_env_variables(input, env_list);
		// printf("here_is\n");
		if (expanded_input != NULL)
		{
			printf("expanded: %s\n", expanded_input);
			free(expanded_input);
		}
		free(input);
	}
	rl_clear_history();
	free_env_list(env_list);
	return (0);
}

// < in ls -l | wc -c > out | cat << g | echo "Hello World!" >> out | echo "No $PWD" | echo 'Yes $SHLVL'