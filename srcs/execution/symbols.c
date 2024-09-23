/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:16:45 by dyao              #+#    #+#             */
/*   Updated: 2024/09/23 19:07:28 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_next_redirection(int i, t_token **tokens)
{
	while (tokens[i])
	{
		if (tokens[i]->type == 0)
			i++;
		else
			return (tokens[i]->type);
	}
	return (0);
}

void	ft_input(char *file_name)
{
	int		fd;

	fd = open(file_name, O_RDONLY, 0777);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	ft_output(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_append(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0777);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_heredocs(char *end)
{
	char	*input;
	char	*output_str;

	input = readline(">");
	while (input != NULL)
	{
		if (ft_strcmp(input, end) == 0)
		{
			free(input);
			break ;
		}
		if (!output_str)
			output_str = ft_strjoin(output_str, input);
		else
		{
			output_str = ft_strjoin(output_str, "\n");
			output_str = ft_strjoin(output_str, input);
		}
		input = readline(">");
	}
	printf("%s", output_str);
	free (output_str);
	// ft_pipe();
}

