/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ults_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:15:43 by dyao              #+#    #+#             */
/*   Updated: 2024/10/01 12:36:55 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	find_quote_before_equal(char *str, int equal_pos)
{
	int	j;

	j = 0;
	while (str[j] && str[j] != '\'' && str[j] != '\"')
		j++;
	if (j >= equal_pos)
		return (-1);
	return (j);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*output;

	len = ft_strlen(str);
	i = 0;
	j = 0;
	output = malloc((len - 1) * sizeof(char));
	if (!output)
		return (NULL);
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '\'' && str[i] != '\"')
			output[j++] = str[i];
		i++;
	}
	while (str[i])
		output[j++] = str[i++];
	output[j] = '\0';
	return (output);
}

char	*ft_delete_quote_before_equal(char *str)
{
	int	equal_pos;
	int	quote_pos;

	equal_pos = find_equal_sign(str);
	quote_pos = find_quote_before_equal(str, equal_pos);
	if (quote_pos == -1)
		return (ft_strdup(str));
	return (remove_quotes(str));
}

int	ft_compare_strs(char *temp, char *final)
{
	int	i;

	i = 0;
	if (!ft_strcmp(temp, final) || ft_strcmp(temp, final) == 10
		|| ft_strcmp(temp, final) == -51)
		return (1);
	while (temp[i] && final[i])
	{
		if (temp[i] == final[i] && temp[i] == '=')
			return (1);
		else if (temp[i] == final[i])
			i++;
		else
			return (0);
	}
	if (final[i] == '=')
		return (1);
	return (0);
}
