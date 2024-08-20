/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:14:26 by yyakuben          #+#    #+#             */
/*   Updated: 2024/08/18 19:19:21 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_token(char *str)
{
	if (!str || !*str)
		return (_null);
	else if (strcmp(str, "|") == 0)
		return (_pipe);
	else if (strcmp(str, "<") == 0)
		return (_redir_in);
	else if (strcmp(str, ">") == 0)
		return (_redir_out);
	else if (strcmp(str, ">>") == 0)
		return (_append);
	else if (strcmp(str, "<<") == 0)
		return (_heredoc);
	return (_word);
}

t_token	*parse_token(const char *input)
{
	size_t		i;
	size_t		token_count;
	t_token		*tokens;

	i = 0;
	token_count = 0;
	tokens = malloc(sizeof(t_token) * (ft_strlen(input) / 2 + 2));
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i])
			break ;
		if (input[i] == '>' && input[i + 1] == '>')
		{
			tokens[token_count].token = strndup(input + i, 2);
			i++;
			
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			tokens[token_count].token = strndup(input + i, 2);
			i++;
			
		}
		else
			tokens[token_count].token = strndup(input + i, 1);
		tokens[token_count].type = is_token(tokens[token_count].token);
		token_count++;
		i++;
	}
	tokens[token_count].type = _null;
	tokens[token_count].token = NULL;
	return (tokens);
}


void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (tokens == NULL)
		return ;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}