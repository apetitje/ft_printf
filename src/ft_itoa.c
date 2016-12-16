/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 14:05:46 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/11 18:04:12 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_find_range(long long int n, int *is_neg,
		unsigned long long absolute_nb, unsigned long long *nb_cpy)
{
	int				range;

	range = 0;
	if (n < 0)
	{
		*is_neg = 1;
		absolute_nb = (unsigned long long)-n;
	}
	else
		absolute_nb = (unsigned long long)n;
	*nb_cpy = absolute_nb;
	while (absolute_nb >= 10)
	{
		absolute_nb = absolute_nb / 10;
		range++;
	}
	range++;
	return (range);
}

char		*ft_itoa(long long int n, int *range)
{
	unsigned long long	absolute_nb;
	char				*number;
	int					is_neg;
	unsigned long long	nb_cpy;
	int					rangecpy;

	absolute_nb = 0;
	is_neg = 0;
	*range = ft_find_range(n, &is_neg, absolute_nb, &nb_cpy);
	rangecpy = *range;
	if (!(number = (char *)malloc(sizeof(char) * (rangecpy + is_neg + 1))))
		return (NULL);
	number[rangecpy + is_neg] = '\0';
	rangecpy--;
	while (nb_cpy >= 10)
	{
		number[rangecpy + is_neg] = nb_cpy % 10 + 48;
		nb_cpy = nb_cpy / 10;
		rangecpy--;
	}
	number[rangecpy + is_neg] = nb_cpy + 48;
	if (is_neg == 1)
		number[0] = '-';
	*range += is_neg;
	return (number);
}
