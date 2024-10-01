/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:35:38 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/01 18:09:46 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocate_args(char *cmd)
{
	int		parts;
	char	**args;
	int		i;

	parts = ft_get_parts(cmd);
	args = malloc(sizeof(char *) * (parts + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (i <= parts)
		args[i++] = NULL;
	return (args);
}

char	*extract_single_quote(char *cmd, int *i)
{
	int		l;
	int		j;
	char	*str;

	l = ++(*i);
	j = 0;
	while (cmd[*i] && cmd[*i] != '\'')
	{
		(*i)++;
		j++;
	}
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (l < *i)
		str[j++] = cmd[l++];
	str[j] = '\0';
	(*i)++;
	return (str);
}

char	*extract_double_quote(char *cmd, int *i)
{
	int		l;
	int		j;
	char	*str;

	l = ++(*i);
	j = 0;
	while (cmd[*i] && cmd[*i] != '\"')
	{
		(*i)++;
		j++;
	}
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (l < *i)
		str[j++] = cmd[l++];
	str[j] = '\0';
	(*i)++;
	return (str);
}

char	*extract_word(char *cmd, int *i)
{
	int		l;
	int		j;
	char	*str;

	l = *i;
	j = 0;
	while (cmd[*i] && cmd[*i] != ' ')
	{
		(*i)++;
		j++;
	}
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (l < *i)
		str[j++] = cmd[l++];
	str[j] = '\0';
	return (str);
}

char	**ft_deal_cmd(char *cmd)
{
	char	**args;
	int		i;
	int		k;

	i = 0;
	k = 0;
	ft_split(cmd, ' ');
	args = allocate_args(cmd);
	if (!args)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			args[k++] = extract_single_quote(cmd, &i);
		else if (cmd[i] == '\"')
			args[k++] = extract_double_quote(cmd, &i);
		else if (cmd[i] == ' ')
			i++;
		else
			args[k++] = extract_word(cmd, &i);
	}
	return (args);
}
