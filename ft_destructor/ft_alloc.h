/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:04:59 by yyakuben          #+#    #+#             */
/*   Updated: 2024/08/07 18:06:33 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ALLOC_H
# define FT_ALLOC_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct t_allocs
{
	void			*ptr;
	struct t_allocs	*next;
}					t_allocs;

/* init */
bool				ft_alloc_init(void);

/* allocations */
void				*ft_calloc(size_t count, size_t size);
void				*ft_malloc(size_t size);

/* utils */
t_allocs			*ft_allocs(t_allocs *lst);

void				add_allocnode(t_allocs **lst, t_allocs *nnew);
t_allocs			*create_alloc(void *ptr);
int					ft_allocsize(void);

/* destructors */
void				ft_free(void *ptr);
void				ft_destructor(void);

#endif
