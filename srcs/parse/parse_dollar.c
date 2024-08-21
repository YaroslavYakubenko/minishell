/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:51:30 by yyakuben          #+#    #+#             */
/*   Updated: 2024/08/21 21:11:39 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_dollar(char *pos)
{
	t_mshell	e_code;
	
	if (*pos == '$' && *(pos + 1) == '$')
	{
		e_code.exit_code = getpid();
		printf("Your pid: %d\n", e_code.exit_code);
	}
	else if (*pos == '$' && *(pos + 1) == '?')
	{
		e_code.exit_code = 0;	
		printf("Your last completed command: %d\n", e_code.exit_code);
	}
}

char	*expand_env_variables(const char *input, t_env *env)
{
	char	*result;
	char	*pos;
	char	*new_result;
	t_mshell		e_code;

	result = strdup(input);
	if (!result)
		return (NULL);
	pos = result;
	while ((pos = strchr(pos, '$')))
	{
		new_result = replace_var_with_value(result, pos, env);
		// printf("here_is_expand\n");
		if (*(pos + 1) == '$' || *(pos + 1) == '?')
		{
			e_code.exit_code = getpid();
			printf("%d\n", e_code.exit_code);
			// return (0);
			break ;
		}
		if (!new_result)
		{
			free(result);
			return (NULL);
		}
		pos = new_result + (pos - result) + strlen(new_result) - strlen(result);
		// printf("%s/n", pos);
		free(result);
		result = new_result;
	}
	printf("result: %s\n", result);
	printf("new_result: %s\n", new_result);
	return (result);
}

