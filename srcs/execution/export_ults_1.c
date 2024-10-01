/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ults_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:31:11 by dyao              #+#    #+#             */
/*   Updated: 2024/10/01 11:31:40 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_deal_record_v5(char *str)
{
	int		i;
	int		j;
	char	*output;

	i = ft_strlen(str);
	output = malloc((i - 1) * sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		else
			output[j++] = str[i++];
	}
	output[j] = '\0';
	return (output);
}

char	*ft_deal_record_v4(char *str)
{
	char	*output;
	int		i;

	if (ft_strchr(str, '\"'))
	{
		output = ft_strdup(str);
		i = ft_strlen(str);
		output[i - 1] = '\'';
		output[i - 2] = '\'';
		return (output);
	}
	else
		return (ft_strdup(str));
}

char	*ft_deal_record_v3(char *str)
{
	char	*output;
	int		i;
	int		j;

	if (ft_strchr(str, '\"') || ft_strchr(str, '\''))
	{
		i = ft_strlen(str);
		output = malloc((i - 1) * sizeof(char));
		if (!output)
			return (NULL);
		i = 0;
		j = 0;
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				i++;
			else
				output[j++] = str[i++];
		}
		output[j] = '\0';
		return (output);
	}
	else
		return (ft_strdup(str));
}

char	*ft_deal_record_v2(char *str)
{
	char	*output;
	int		i;

	i = ft_strlen(str);
	output = malloc((i + 3) * sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	while (str[i])
	{
		output[i] = str[i];
		i++;
	}
	output[i++] = '\'';
	output[i++] = '\'';
	output[i] = '\0';
	return (output);
}

char	*ft_deal_record(int mark, char *str)
{
	if (mark == 5)
		return (ft_deal_record_v5(str));
	else if (mark == 4)
		return (ft_deal_record_v4(str));
	else if (mark == 3)
		return (ft_deal_record_v3(str));
	else if (mark == 2)
		return (ft_deal_record_v2(str));
	else
		return (ft_strdup(str));
}
