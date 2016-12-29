/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 20:50:12 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/29 19:46:09 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_precision(t_arg *ele, int i, const char *str)
{
	if (ft_isdigit(str[i + 1]))
	{
		ele->precision = ft_atoi(str + i + 1);
		if (ele->precision == 0)
			ele->precision = -1;
		++i;
		while (str[i] && ft_isdigit(str[i]))
			++i;
		--i;
	}
	else
		ele->precision = -1;
	return (i);
}

void			ft_flags_num(t_out *output, t_arg *ele)
{
	if (ele->hash && ((ele->type == 'o') || ele->type == 'O'
				|| (ele->format == 'u' && ele->data.u > 0)
				|| (ele->format == 'U' && ele->data.lu > 0)
				|| (ele->format == 'K' && ele->data.llu > 0)))
	{
		ft_fill_out(output, "0", 1);
		if (ele->type != 'o' && ele->type != 'O')
		{
			ft_fill_out(output, &ele->type, 1);
			ele->sharp = 1;
		}
	}
	if (((ele->type == 'i' || ele->type == 'd') && ele->data.d >= 0)
				|| (ele->type == 'D' && ele->data.ld >= 0)
				|| (ele->type == 'f' && ele->data.f >= 0.0))
	{
		if (ele->plus)
			ft_fill_out(output, "+", 1);
		else if (ele->space)
			ft_fill_out(output, " ", 1);
	}
}
