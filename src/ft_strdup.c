/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 21:57:11 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/19 18:14:44 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dst;

	i = ft_strlen(s1);
	if (!(dst = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	dst = ft_memcpy(dst, s1, i);
	dst[i] = '\0';
	return (dst);
}
