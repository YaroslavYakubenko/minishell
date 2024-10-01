/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:37:59 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/01 19:19:32 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_vars(int *i, int *j,
	int *in_single_quote, int *in_double_quote)
{
	*i = 0;
	*j = 0;
	*in_single_quote = 0;
	*in_double_quote = 0;
}

int	is_space_and_not_in_quotes(char c, int in_single_quote, int in_double_quote)
{
	return (c == ' ' && !in_single_quote && !in_double_quote);
}

void	handle_spaces(char *input, int *i, char *result, int *j)
{
	result[(*j)++] = ' ';
	while (input[*i] == ' ')
		(*i)++;
}

char	*compress_spaces(char *input)
{
	char	*result;
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;

	result = malloc(ft_strlen(input) + 1);
	if (!result)
		return (NULL);
	initialize_vars(&i, &j, &in_single_quote, &in_double_quote);
	while (input[i])
	{
		check_quotes(input[i], &in_single_quote, &in_double_quote);
		if (is_space_and_not_in_quotes(input[i],
				in_single_quote, in_double_quote))
			handle_spaces(input, &i, result, &j);
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

// char	*compress_spaces(char *input)
// {
// 	int		i;
// 	int		j;
// 	char	*result;
// 	int		in_single_quote;
// 	int		in_double_quote;

// 	i = 0;
// 	j = 0;
// 	in_single_quote = 0;
// 	in_double_quote = 0;
// 	result = malloc(ft_strlen(input) + 1);
// 	if (!result)
// 		return (NULL);
// 	while (input[i])
// 	{
// 		check_quotes(input[i], &in_single_quote, &in_double_quote);
// 		if (input[i] == ' ' && !in_single_quote && !in_double_quote)
// 		{
// 			result[j++] = ' ';
// 			while (input[i] == ' ')
// 				i++;
// 		}
// 		else
// 			result[j++] = input[i++];
// 	}
// 	result[j] = '\0';
// 	return (result);
// }