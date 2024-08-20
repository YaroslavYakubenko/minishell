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
	
	(void)ac;
	(void)av;
	env_list = init_new_list(envp);
	while ((input = readline("minishell%")) != NULL)
	{
		if (*input)
			add_history(input);
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