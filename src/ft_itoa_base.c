/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 15:32:22 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/19 17:09:29 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_itoa_base(unsigned long int nb, size_t base,
		char *base_str, int *range)
{
	char			*number;
	char			num[100];
	int				i;

	i = 98;
	num[99] = '\0';
	while (nb >= base)
	{
		num[i] = base_str[nb % base];
		nb = nb / base;
		--i;
	}
	num[i] = base_str[nb];
	*range = 98 - i + 1;
	number = ft_strdup(num + i);
	return (number);
}
