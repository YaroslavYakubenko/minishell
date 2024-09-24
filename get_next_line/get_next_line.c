/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:03:16 by dyao              #+#    #+#             */
/*   Updated: 2024/09/24 19:38:14 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_buffer(char *buffer, int fd)
{
	char	*temp_buff;
	int		bytesread;

	temp_buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_buff)
		return (NULL);
	bytesread = 1;
	while (!ft_strchr_1(buffer, '\n') && bytesread != 0)
	{
		bytesread = read(fd, temp_buff, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free(temp_buff);
			return (NULL);
		}
		temp_buff[bytesread] = '\0';
		buffer = ft_strjoin_1(buffer, temp_buff);
	}
	free(temp_buff);
	return (buffer);
}

char	*ft_deal_buffer(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	str = (char *)malloc((i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		str[j] = buffer[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_return_rest(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	str = (char *)malloc((ft_strlen_1(buffer) - i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i++;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	free (buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*store;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = ft_read_buffer(buffer, fd);
	if (buffer == NULL)
		return (NULL);
	store = ft_deal_buffer(buffer);
	buffer = ft_return_rest(buffer);
	return (store);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("example.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	line = get_next_line(fd);
// 	printf("the line is :%s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("the line is :%s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("the line is :%s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("the line is :%s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("the line is :%s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("the line is :%s\n", line);
// 	free(line);

// 	close(fd);
// 	return (0);
// }
