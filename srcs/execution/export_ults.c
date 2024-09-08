/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ults.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:14:50 by dyao              #+#    #+#             */
/*   Updated: 2024/09/08 12:47:16 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char )*s1 - (unsigned char)*s2);
}

void	ft_unset(char **record, char *str)
{
	int	i;

	i = 0;
	while (record[i])
	{
		if (ft_strcmp(record[i], str) == 0)
		{
			free(record[i]);
			while (record[i + 1])
			{
				record[i] = record[i + 1];
				i++;
			}
		}
		else
			i++;
	}
}

void	ft_record(char *str, char *result)
{
	int			j;
	char		*final;

	j = ft_strlen(str);
	final = malloc((j + 3) * sizeof(char));
	if (!final)
		return ;
	final = ft_output_final(final, str);
	result = final;
}
