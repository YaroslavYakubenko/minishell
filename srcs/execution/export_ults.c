/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ults.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:14:50 by dyao              #+#    #+#             */
/*   Updated: 2024/09/11 14:32:40 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char )*s1 - (unsigned char)*s2);
}

int	ft_unset(char **record, char *str, int j)
{
	int		i;
	char	*temp;

	i = 0;
	while (record[i])
	{
		if (ft_strcmp(record[i], str) == 0 || ft_strcmp(record[i], str) == 61)
		{
			free(record[i]);
			record[i] = NULL;
			while (record[i + 1])
			{
				temp = record[i];
				record[i] = record[i + 1];
				record[i + 1] = temp;
				i++;
			}
			--j;
		}
		else
			i++;
	}
	return (j);
}

char	*ft_output_final(char *final, char *str)
{
	int		k;
	int		j;

	k = 0;
	while (str[k] != '=' && str[k])
	{
		final[k] = str[k];
		k++;
	}
	if (str[k] == '=')
	{
		final[k] = str[k];
		k++;
		j = k;
		final[j++] = '"';
		while (str[k])
			final[j++] = str[k++];
		final[j++] = '"';
		final[j] = '\0';
	}
	else
		final[k] = '\0';
	return (final);
}

char	*ft_record(char *str)
{
	int			j;
	char		*final;

	j = ft_strlen(str);
	final = malloc((j + 4) * sizeof(char));
	if (!final)
		return (NULL);
	final = ft_output_final(final, str);
	return (final);
}

void	ft_put_null(char **record)
{
	int	i;

	i = 0;
	while (i <= 254)
	{
		record[i] = NULL;
		i++;
	}
}
