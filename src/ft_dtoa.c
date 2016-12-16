/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 14:05:46 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/13 16:43:54 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_end(char *number, char *floor, char *after, int *range)
{
	number = ft_strjoin(floor, after);
	free(floor);
	free(after);
	*range = ft_strlen(number);
	return (number);
}

char			*ft_dtoa(double n, int prec, int *range)
{
	int		i;
	char	*number;
	char	*floor;
	char	*after;

	number = NULL;
	i = 0;
	if (n != n)
		return (ft_strdup("NaN"));
	if (prec == -1)
		return (ft_itoa((long long int)n, range));
	n += ((n < 0) ? -1 : 1) * ft_pow(10.0, -prec) * 0.5;
	floor = ft_itoa((long long int)n, range);
	n = (n < 0) ? -(n - (long long int)n) : (n - (long long int)n);
	if (!(after = (char *)malloc(sizeof(char) * (prec + 2))))
		exit(EXIT_FAILURE);
	after[0] = '.';
	after[prec + 1] = '\0';
	while (++i <= prec)
	{
		after[i] = (int)(n * 10) + 48;
		n = n * 10 - (int)(n * 10);
	}
	number = ft_end(number, floor, after, range);
	return (number);
}
