/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 14:05:46 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/19 17:17:03 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_itoa(long long int n, int *range)
{
	char				*number;
	int					is_neg;
	unsigned long long	nb_cpy;
	char				inv[100];
	int					i;

	i = 98;
	is_neg = 0;
	if (n < 0)
		is_neg = 1;
	nb_cpy = (n < 0) ? (unsigned long long)-n : (unsigned long long)n;
	inv[99] = '\0';
	while (nb_cpy >= 10)
	{
		inv[i] = nb_cpy % 10 + 48;
		nb_cpy = nb_cpy / 10;
		--i;
	}
	inv[i] = nb_cpy + 48;
	if (is_neg == 1)
		inv[--i] = '-';
	*range = 98 - i + 1;
	number = ft_strdup(inv + i);
	return (number);
}
