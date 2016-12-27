/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 15:50:20 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 12:22:27 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t size)
{
	void	*dup;

	dup = NULL;
	if (size)
		if (!(dup = (char *)malloc(size)))
			return (NULL);
	if (ptr && dup)
	{
		ft_memcpy(dup, ptr, size);
		ft_memdel(&ptr);
	}
	(*(char *)(dup + size - 1)) = '\0';
	return (dup);
}
