/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:10:33 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/01 17:46:37 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_error(const char *input, size_t i)
{
	if (i == 0 || input[i + 1] == '\0')
		return (1);
	if (input[i + 1] == '|')
		return (1);
	return (0);
}

int	check_redirect_error(const char *input, size_t i)
{
	if (input[i + 1] == '>' || input[i + 1] == '<' || input[i + 1] == '|')
		return (1);
	return (0);
}
