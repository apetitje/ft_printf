/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 15:32:22 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/11 18:04:59 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char		*ft_is_base(size_t base, char size)
{
	char			*base_str;
	char			digit;
	size_t			i;

	digit = '0';
	i = 0;
	if (!(base_str = (char *)malloc(sizeof(char) * (base + 1))))
		exit(EXIT_FAILURE);
	while (i < base)
	{
		base_str[i] = digit;
		i++;
		digit++;
		if (digit == ':')
		{
			if (size == 'x')
				digit = 'a';
			else if (size == 'X')
				digit = 'A';
		}
	}
	base_str[i] = '\0';
	return (base_str);
}

static int		ft_find_range(unsigned long int nb, size_t base)
{
	int				range;

	range = 0;
	while (nb >= base)
	{
		nb = nb / base;
		range++;
	}
	range++;
	return (range);
}

char			*ft_itoa_base(unsigned long int nb, size_t base,
		char size, int *range)
{
	char			*number;
	char			*base_str;
	int				rangecpy;

	base_str = ft_is_base(base, size);
	*range = ft_find_range(nb, base);
	rangecpy = *range;
	if (!(number = (char *)malloc(sizeof(char) * (rangecpy + 1))))
		exit(EXIT_FAILURE);
	number[rangecpy] = '\0';
	rangecpy--;
	while (nb >= base)
	{
		number[rangecpy] = base_str[nb % base];
		nb = nb / base;
		rangecpy--;
	}
	number[rangecpy] = base_str[nb];
	free(base_str);
	return (number);
}
