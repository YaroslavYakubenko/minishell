/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ults_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:03:11 by dyao              #+#    #+#             */
/*   Updated: 2024/10/01 12:07:28 by dyao             ###   ########.fr       */
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

int	open_file_1(char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags);
	if (fd < 0)
		return (-1);
	return (fd);
}

char	*read_and_filter_lines(int fd, char *str)
{
	char	*temp;
	char	*temp2;
	int		count;

	temp2 = NULL;
	count = 0;
	temp = get_next_line(fd);
	while (temp)
	{
		if (ft_strcmp(temp, str) != 0 && ft_strcmp(temp, str) != 61
			&& ft_strcmp(temp, str) != 10)
		{
			if (count++ == 0)
				temp2 = ft_strdup(temp);
			else
				temp2 = ft_strjoin(temp2, temp);
		}
		free(temp);
		temp = get_next_line(fd);
	}
	return (temp2);
}

int	write_to_file_1(char *filename, char *content)
{
	int	fd;

	fd = open(filename, O_RDWR | O_TRUNC);
	if (fd < 0)
		return (0);
	if (content)
		write(fd, content, ft_strlen(content));
	close(fd);
	return (1);
}

void	ft_unset(char *str)
{
	int		fd;
	char	*temp2;

	fd = open_file_1("index", O_RDWR);
	if (fd < 0)
		return ;
	temp2 = read_and_filter_lines(fd, str);
	close(fd);
	if (!write_to_file_1("index", temp2))
	{
		free(temp2);
		return ;
	}
	free(temp2);
}
