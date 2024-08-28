/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:07:25 by yyakuben          #+#    #+#             */
/*   Updated: 2024/08/28 19:55:49 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		is_quote(char c)
// {
// 	if (c == '\'' || c == '\"')
// 		return (1);
// 	return (0);
// }

// int		is_escape(char c)
// {
// 	if (c == '\\')
// 		return (1);
// 	return (0);
// }

// int		is_quote_end(char c, char quote)
// {
// 	if (c == quote)
// 		return (1);
// 	return (0);
// }

// int		is_quote_start(char c)
// {
// 	if (c == '\'' || c == '\"')
// 		return (1);
// 	return (0);
// }


// void	parse_quotes(char *input)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	quote;

// 	i = 0;
// 	j = 0;
// 	quote = 0;
// 	while (input[i])
// 	{
// 		if (is_quote_start(input[i]))
// 		{
// 			quote = input[i];
// 			i++;
// 		}
// 		if (is_quote_end(input[i], quote))
// 		{
// 			quote = 0;
// 			i++;
// 		}
// 		if (is_escape(input[i]))
// 			i++;
// 		i++;
// 	}
// }

char	*parse_quotes(char *input)
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

char	*parse_quotes1(char *input)
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