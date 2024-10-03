/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:10:33 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/03 22:24:14 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char *cmd, int *i)
{
	char	quote;

	quote = cmd[*i];
	(*i)++;
	while (cmd[*i] && cmd[*i] != quote)
		(*i)++;
	if (cmd[*i])
		(*i)++;
}

void	fill_result(char *cmd, int start, int end, char *result)
{
	int	k;

	k = 0;
	while (start < end)
	{
		if (cmd[start] != '\'' && cmd[start] != '\"')
			result[k++] = cmd[start];
		start++;
	}
	result[k] = '\0';
}

// int	has_invalid_pipe_or_redirects(const char *cmd_line)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd_line[i])
// 	{
// 		if (cmd_line[i] == '|' || cmd_line[i] == '<' || cmd_line[i] == '>')
// 		{
// 			if (i == 0 || cmd_line[i + 1] == '\0')
// 				return (1);
// 			if (cmd_line[i] == '<' && cmd_line[i + 1] == '<')
// 				return (1);
// 			if (cmd_line[i] == '>' && cmd_line[i + 1] == '>')
// 				return (1);
// 			if (ft_isspace((unsigned char)cmd_line[i + 1]))
// 			{
// 				while (ft_isspace((unsigned char)cmd_line[i + 1]))
// 					i++;
// 				if (cmd_line[i + 1] == '\0' || cmd_line[i + 1] == '|')
// 					return (1);
// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }


int	has_invalid_pipe_or_redirects(const char *cmd_line)
{
	int		i;
	int		in_single_quote;
	int		in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;

	while (cmd_line[i])
	{
		if (cmd_line[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			i++;
			continue ;
		}
		else if (cmd_line[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			i++;
			continue ;
		}
		if (!in_single_quote && !in_double_quote)
		{
			if (cmd_line[i] == '|' || cmd_line[i] == '<' || cmd_line[i] == '>')
			{
				if (i == 0 || cmd_line[i + 1] == '\0')
					return (1);
				if ((cmd_line[i] == '<' && cmd_line[i + 1] == '<')
					|| (cmd_line[i] == '>' && cmd_line[i + 1] == '>'))
					i++;
				if (ft_isspace((unsigned char)cmd_line[i + 1]))
				{
					while (ft_isspace((unsigned char)cmd_line[i + 1]))
						i++;
					if (cmd_line[i + 1] == '\0' || cmd_line[i + 1] == '|')
						return (1);
				}
			}
		}
		i++;
	}
	return (0);
}

// int has_invalid_pipes(const char *cmd_line)
// {
//     int i = 0;

//     // Пропускаем начальные пробелы
//     while (ft_isspace(cmd_line[i]))
//         i++;

//     // Проверка на пайп в начале строки
//     if (cmd_line[i] == '|')
//         return 1;

//     while (cmd_line[i])
//     {
//         // Проверяем на наличие пайпа
//         if (cmd_line[i] == '|')
//         {
//             // Пропускаем пробелы после пайпа
//             i++;
//             while (ft_isspace(cmd_line[i]))
//                 i++;

//             // Проверка, чтобы после пайпа была не пустая команда
//             if (cmd_line[i] == '|' || cmd_line[i] == '\0')
//                 return 1;
//         }
//         else
//             i++;
//     }

//     // Проверка на пайп в конце строки
//     i--;
//     while (i >= 0 && ft_isspace(cmd_line[i]))
//         i--;
//     if (cmd_line[i] == '|')
//         return 1;

//     return 0;
// }

// int	has_invalid_pipe_syntax(const char *cmd_line)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd_line[i])
// 	{
// 		if (cmd_line[0] == '|')
// 			return (1);
// 		else if (cmd_line[i] == '|' && cmd_line[i + 1] == '|')
// 			return (1);
// 		else if (cmd_line[i] == '|' && cmd_line[i + 1] == '\0')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
