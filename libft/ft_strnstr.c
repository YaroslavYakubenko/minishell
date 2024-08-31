/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:32:37 by yyakuben          #+#    #+#             */
/*   Updated: 2023/12/06 18:34:09 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*c1;
	const char	*c2;
	int			traverse;
	size_t		count;

	c1 = haystack;
	c2 = needle;
	traverse = 0;
	count = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*c1 && *c2 && count++ <= len)
	{
		if (*c1 == *c2)
		{
			while ((*(c1 + traverse) == *(c2 + traverse)) && count++ <= len)
			{
				if (*(c2 + traverse + 1) == '\0')
					return ((char *)c1);
				traverse++;
			}
		}
		c1++;
	}
	return (NULL);
}
