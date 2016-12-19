/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:52:56 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/19 18:39:25 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)(dst + i)) = *((unsigned char *)(src + i));
		i++;
	}
	return (dst);
}
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	long	*d;
	long	*s;
	char	*d2;
	char	*s2;
	
	d = (long *)dst;
	s = (long *)src;
	while (n >= sizeof(long))
	{
		*d = *s;
		++d;
		++s;
		n -= sizeof(long);
	}
	d2 = (char *)d;
	s2 = (char *)s;
	while (n > 0)
	{
		*d2 = *s2;
		++d2;
		++s2;
		--n;
	}
	return (dst);
}
