/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ults.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:14:50 by dyao              #+#    #+#             */
/*   Updated: 2024/09/24 20:55:37 by dyao             ###   ########.fr       */
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

void ft_unset(char *str) {
    int i;
    int count;
    char *temp;
    char *temp2;

    count = 0;
    temp = NULL;
    temp2 = NULL;
    i = open("index", O_RDWR);
    if (i < 0)
        return;
    temp = get_next_line(i);
    while (temp)
	{
        if (ft_strcmp(temp, str) == 0 || ft_strcmp(temp, str) == 61 || ft_strcmp(temp, str) == 10)
			;
        else if (count++ == 0)
            temp2 = ft_strdup(temp);
        else
            temp2 = ft_strjoin(temp2, temp);
        free(temp);
        temp = get_next_line(i);
    }
    close(i);
    i = open("index", O_RDWR | O_TRUNC);
    if (i < 0)
	{
        free(temp2);
        return;
    }
	if (temp2)
    	write(i, temp2, ft_strlen(temp2));
    close(i);
    free(temp2);
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

void	ft_record(char *str)
{
	int			j;
	char		*final;

	j = ft_strlen(str);
	final = malloc((j + 4) * sizeof(char));
	if (!final)
		return ;
	final = ft_output_final(final, str);
	j = open("index", O_RDWR | O_CREAT | O_APPEND, 0777);
	write(j, final, ft_strlen(final));
	write(j, "\n", 1);
}

void	ft_read_and_print(void)
{
	int		fd;
	char	*temp;

	fd = open("index", O_RDONLY);
	if (fd < 0)
		return ;
	temp = get_next_line(fd);
	if (!temp)
		return ;
	while (temp)
	{
		printf("%s", temp);
		free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
}
