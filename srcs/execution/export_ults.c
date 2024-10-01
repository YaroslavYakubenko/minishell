/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ults.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:14:50 by dyao              #+#    #+#             */
/*   Updated: 2024/10/01 12:36:51 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_equal_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && (str[i + 1] == '\'' || str[i + 1] == '\"')
			&& (str[i + 2] != '\'' && str[i + 2] != '\"'))
			return (5);
		else if (str[i] == '=' && (str[i + 1] == '\'' || str[i + 1] == '\"')
			&& (str[i + 2] == '\'' || str[i + 2] == '\"'))
			return (4);
		else if (str[i] == '=' && str[i + 1] && (str[i + 1] != '\''
				|| str[i + 1] != '\"'))
			return (3);
		else if (str[i] == '=' && !str[i + 1])
			return (2);
		i++;
	}
	return (1);
}

void	ft_record(char *str)
{
	int		j;
	int		mark;
	char	*temp;
	char	*final;

	temp = ft_delete_quote_before_equal(str);
	mark = ft_check_equal_quote(str);
	final = ft_deal_record(mark, temp);
	free(temp);
	if (ft_renew_list(final) != 1)
	{
		j = open("index", O_RDWR | O_CREAT | O_APPEND, 0777);
		write(j, final, ft_strlen(final));
		write(j, "\n", 1);
	}
	free(final);
}

// int	ft_renew_list(char *final)
// {
// 	int		i;
// 	int		count;
// 	int		mark;
// 	char	*temp;
// 	char	*temp2;

// 	count = 0;
// 	mark = 0;
// 	temp = NULL;
// 	temp2 = NULL;
// 	i = open("index", O_RDWR);
// 	if (i < 0)
// 		return (0);
// 	temp = get_next_line(i);
// 	while (temp)
// 	{
// 		if (ft_compare_strs(temp, final) == 1)
// 		{
// 			free(temp);
// 			temp = ft_strjoin(final, "\n");
// 			mark = 1;
// 		}
// 		if (count++ == 0)
// 			temp2 = ft_strdup(temp);
// 		else
// 			temp2 = ft_strjoin_1(temp2, temp);
// 		free(temp);
// 		temp = get_next_line(i);
// 	}
// 	close(i);
// 	i = open("index", O_RDWR | O_TRUNC);
// 	if (i < 0)
// 	{
// 		free(temp2);
// 		return (0);
// 	}
// 	if (temp2)
// 		write(i, temp2, ft_strlen(temp2));
// 	close(i);
// 	free(temp2);
// 	return (mark);
// }

// void	ft_unset(char *str)
// {
// 	int		i;
// 	int		count;
// 	char	*temp;
// 	char	*temp2;

// 	count = 0;
// 	temp = NULL;
// 	temp2 = NULL;
// 	i = open("index", O_RDWR);
// 	if (i < 0)
// 		return ;
// 	temp = get_next_line(i);
// 	while (temp)
// 	{
// 		if (ft_strcmp(temp, str) == 0 || ft_strcmp(temp, str) == 61
// 			|| ft_strcmp(temp, str) == 10)
// 			;
// 		else if (count++ == 0)
// 			temp2 = ft_strdup(temp);
// 		else
// 			temp2 = ft_strjoin(temp2, temp);
// 		free(temp);
// 		temp = get_next_line(i);
// 	}
// 	close(i);
// 	i = open("index", O_RDWR | O_TRUNC);
// 	if (i < 0)
// 	{
// 		free(temp2);
// 		return ;
// 	}
// 	if (temp2)
// 		write(i, temp2, ft_strlen(temp2));
// 	close(i);
// 	free(temp2);
// }

// char	*ft_delete_quote_before_equal(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	*output;

// 	i = 0;
// 	j = 0;
// 	while (str[i] && str[i] != '=')
// 		i++;
// 	while (str[j] && str[j] != '\'' && str[j] != '\"')
// 		j++;
// 	if (j >= i)
// 		return (ft_strdup(str));
// 	i = ft_strlen(str);
// 	output = malloc((i - 1) * sizeof(char));
// 	if (!output)
// 		return (NULL);
// 	j = 0;
// 	i = 0;
// 	while (str[i] && str[i] != '=')
// 	{
// 		if (str[i] == '\'' || str[i] == '\"')
// 			i++;
// 		else
// 			output[j++] = str[i++];
// 	}
// 	while (str[i])
// 		output[j++] = str[i++];
// 	output[j] = '\0';
// 	return (output);
// }