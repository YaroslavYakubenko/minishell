/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:07:11 by yyakuben          #+#    #+#             */
/*   Updated: 2023/12/06 18:35:00 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0 && s[i] != c)
	{
		if (s[i] == (char)c)
			return (&((char *)s)[i]);
		i--;
	}
	if (i < 0)
		return ((char *) NULL);
	return (&((char *)s)[i]);
}
