/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ultes_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:54:25 by dyao              #+#    #+#             */
/*   Updated: 2024/10/01 11:56:36 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags);
	if (fd < 0)
		return (-1);
	return (fd);
}

char	*read_and_process_lines(int fd, char *final, int *mark)
{
	char	*temp;
	char	*temp2;
	int		count;

	count = 0;
	temp2 = NULL;
	temp = get_next_line(fd);
	while (temp)
	{
		if (ft_compare_strs(temp, final) == 1)
		{
			free(temp);
			temp = ft_strjoin(final, "\n");
			*mark = 1;
		}
		if (count++ == 0)
			temp2 = ft_strdup(temp);
		else
			temp2 = ft_strjoin_1(temp2, temp);
		free(temp);
		temp = get_next_line(fd);
	}
	return (temp2);
}

int	write_to_file(char *filename, char *content)
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

int	ft_renew_list(char *final)
{
	int		mark;
	int		fd;
	char	*temp2;

	mark = 0;
	fd = open_file("index", O_RDWR);
	if (fd < 0)
		return (0);
	temp2 = read_and_process_lines(fd, final, &mark);
	close(fd);
	if (!write_to_file("index", temp2))
	{
		free(temp2);
		return (0);
	}
	free(temp2);
	return (mark);
}

void	ft_read_and_print(void)
{
	int		fd;
	int		i;
	char	*temp;

	fd = open("index", O_RDONLY);
	if (fd < 0)
		return ;
	temp = get_next_line(fd);
	if (!temp)
		return ;
	while (temp)
	{
		i = 0;
		while (temp[i])
		{
			if (temp[i] == '=')
				printf("%s", temp);
			i++;
		}
		free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
}
