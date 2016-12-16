/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 15:50:20 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/16 10:05:04 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t size)
{
	void	*dup;

	dup = NULL;
	if (size)
		dup = ft_memalloc(size);
	if (ptr && dup)
	{
		ft_memcpy(dup, ptr, size);
		ft_memdel(&ptr);
	}
	return (dup);
}
