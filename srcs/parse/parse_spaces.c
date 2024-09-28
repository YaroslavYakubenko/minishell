/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:37:59 by yyakuben          #+#    #+#             */
/*   Updated: 2024/09/28 16:16:51 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*compress_spaces(char *input)
{
	int		i;
	int		j;
	char	*result;
	int		in_single_quote;
	int		in_double_quote;

	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	result = malloc(ft_strlen(input) + 1);
	if (!result)
		return (NULL);
	while (input[i])
	{
		check_quotes(input[i], &in_single_quote, &in_double_quote);
		if (input[i] == ' ' && !in_single_quote && !in_double_quote)
		{
			result[j++] = ' ';
			while (input[i] == ' ')
				i++;
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*expand_and_compress(char *input, t_env *env)
{
	t_env	*temp;
	char	*expanded;
	char	*compressed;

	expanded = expand_env_variables(input, env);
	if (!expanded)
		return (NULL);
	compressed = compress_spaces(expanded);
	free(expanded);
	free(input);
	while (env)
	{
		temp = env->next;
		free(env->name);
		free(env->val);
		free(env);
		env = temp;
	}
	return (compressed);
}
