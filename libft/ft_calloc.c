/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:56:15 by yyakuben          #+#    #+#             */
/*   Updated: 2023/11/15 15:55:48 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*pointer;

	pointer = malloc(nitems * size);
	if (pointer == NULL)
		return (NULL);
	ft_bzero(pointer, nitems * size);
	return (pointer);
}
