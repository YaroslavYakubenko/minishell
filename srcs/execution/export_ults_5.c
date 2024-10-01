/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ults_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:32:25 by dyao              #+#    #+#             */
/*   Updated: 2024/10/01 12:33:06 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_lines_in_file(char *filename)
{
	int		fd;
	int		count;
	char	*temp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	temp = get_next_line(fd);
	while (temp)
	{
		count++;
		free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char	**allocate_output_array(char **store, int file_line_count)
{
	int		store_count;
	char	**output;

	store_count = 0;
	while (store[store_count])
		store_count++;
	output = malloc((file_line_count + store_count + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	return (output);
}

void	copy_store_to_output(char **store, char **output)
{
	int	i;

	i = 0;
	while (store[i])
	{
		output[i] = ft_strdup(store[i]);
		i++;
	}
}

void	read_lines_and_add_to_output(char *filename,
		char **output, int start_index)
{
	int		fd;
	int		j;
	char	*temp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	temp = get_next_line(fd);
	while (temp)
	{
		j = 0;
		while (temp[j] != '\n' && temp[j])
			j++;
		temp[j] = '\0';
		output[start_index++] = temp;
		temp = get_next_line(fd);
	}
	output[start_index] = NULL;
	close(fd);
}

char	**ft_add_list(char **store)
{
	int		file_line_count;
	char	**output;

	file_line_count = count_lines_in_file("index");
	if (file_line_count < 0)
		return (store);
	output = allocate_output_array(store, file_line_count);
	if (!output)
		return (NULL);
	copy_store_to_output(store, output);
	read_lines_and_add_to_output("index", output, file_line_count);
	ft_free_double_pointer_char(store);
	return (output);
}
