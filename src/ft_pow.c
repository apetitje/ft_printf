/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 12:07:08 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/13 12:07:49 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_pow(double pow, int nb)
{
	double	n;

	n = pow;
	if (nb > 0)
	{
		while (nb > 1)
		{
			pow = pow * n;
			nb--;
		}
	}
	else
	{
		while (nb <= 0)
		{
			pow = pow / n;
			nb++;
		}
	}
	return (pow);
}
