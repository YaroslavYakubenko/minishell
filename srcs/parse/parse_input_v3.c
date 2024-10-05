/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_v3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:13:45 by dyao              #+#    #+#             */
/*   Updated: 2024/10/05 15:50:09 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quote(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			j = 1;
		i++;
	}
	return (j);
}

char	*get_input(void)
{
	char	*input;

	input = readline("minishell% ");
	if (!input)
	{
		free(input);
		printf("exit\n");
		exit(0);
	}
	if (*input)
		add_history(input);
	return (input);
}

int	check_syntax(char *input)
{
	if (!are_quotes_closed(input))
	{
		printf("Error: syntax error with quotes\n");
		return (1);
	}
	if (has_invalid_pipe_or_redirects(input))
	{
		printf("Error: syntax error with pipes or redirects\n");
		return (1);
	}
	return (0);
}

void	handle_command(char *expanded_input, char **evnp)
{
	t_cmd	*cmd;

	cmd = ft_start_parse(expanded_input, evnp);
	if (!cmd)
		return ;
	ft_give_marks(cmd);
	ft_handle_cmd_mark(cmd);
	ft_start(cmd);
}
