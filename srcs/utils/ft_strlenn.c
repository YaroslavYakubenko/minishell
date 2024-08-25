/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:41:13 by yyakuben          #+#    #+#             */
/*   Updated: 2024/08/23 15:43:44 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlenn(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != ' ' && str[len] != '\0')
		len++;
	return (len);
}