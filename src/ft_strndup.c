/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 21:57:11 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 12:22:41 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

char	*ft_strndup(const char *s1, size_t len)
{
	char	*dst;

	if (!(dst = ft_memalloc(len + 1)))
		return (NULL);
	dst = ft_strncpy(dst, s1, len);
	dst[len] = '\0';
	return (dst);
}
