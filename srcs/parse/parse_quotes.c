/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:07:25 by yyakuben          #+#    #+#             */
/*   Updated: 2024/09/09 23:47:03 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_single_quotes(char *input)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	str = NULL;
	if (input[i] == '\'' && input[i])
	{
		if (input[i] == '\'')
		{
			j = 0;
			i++;
			while (input[i] != '\'')
			{
				if (input[i] == '\0')
				{
					printf("minishell: syntax error with \'\n");
					return (NULL);
				}
				j++;
				i++;
			}
			str = strndup(&input[i - j], j);
		}
	}
	return (str);
}

char	*parse_double_quotes(char *input)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	str = NULL;
	if (input[i] == '\"' && input[i])
	{
		if (input[i] == '\"')
		{
			j = 0;
			i++;
			while (input[i] != '\"')
			{
				if (input[i] == '\0')
				{
					printf("minishell: syntax error with \"\n");
					return (NULL);
				}
				j++;
				i++;
			}
			str = strndup(&input[i - j], j);
		}
	}
	return (str);
}

void	check_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
	else if (c == '\'' && !(*in_double_quote))
			*in_single_quote = !(*in_single_quote);
}
