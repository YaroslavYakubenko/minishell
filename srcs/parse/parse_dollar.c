/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:51:30 by yyakuben          #+#    #+#             */
/*   Updated: 2024/08/18 22:19:19 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env_variables(const char *input, t_env *env)
{
	char	*result;
	char	*pos;
	char	*new_result;

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
			printf("command not found: \n");
			return (0);
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
	return (result);
}

