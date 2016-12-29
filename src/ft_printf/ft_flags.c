/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 20:50:12 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/29 15:40:15 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_precision(t_arg *ele, int i)
{
	if (ft_isdigit(ele->flag[i + 1]))
	{
		ele->precision = ft_atoi(ele->flag + i + 1);
		if (ele->precision == 0)
			ele->precision = -1;
		++i;
		while (ele->flag[i] && ft_isdigit(ele->flag[i]))
			++i;
		--i;
	}
	else
		ele->precision = -1;
	return (i);
}

void			ft_flags_all(t_arg *ele, va_list ap)
{
	int		i;

	i = -1;
	if (ele->type == '\0')
		return ;
	while (ele->flag[++i])
	{
		if (ele->flag[i] == '#')
			ele->hash = 1;
		else if (ele->flag[i] == '+')
			ele->plus = 1;
		else if (ele->flag[i] == ' ')
			ele->space = 1;
		else if (ele->flag[i] == '-')
			ele->padleft = 1;
		else if (ele->flag[i] == '*')
		{
			if (i == 0 || ele->flag[i - 1] != '.')
				ele->pad = va_arg(ap, int);
			else
			{
				ele->precision = va_arg(ap, int);
				if (ele->precision == 0)
					ele->precision = -1;
			}
			ele->wild = 1;
		}
		else if (ele->flag[i] == '0')
		{
			if (i == 0 || ft_isdigit(ele->flag[i - 1]) == 0)
				ele->zero = 1;
		}
		else if (ft_isdigit(ele->flag[i]) && (i == 0 || ele->flag[i - 1] != '.'))
			i = ft_find_pad(ele, i);
		else if (ele->flag[i] == '.' && ele->flag + i + 1)
			i = ft_precision(ele, i);
	}
	if (ele->zero && (((ft_strchr("scSC%Z", ele->type) || ele->precision == 0) && !ele->padleft) || (ele->precision != 0 && ele->wild)))
		ele->padchar = '0';
}

static void		ft_is_plus(t_out *str, t_arg *ele)
{
	if (((ele->type == 'i' || ele->type == 'd') && ele->data.d >= 0)
				|| (ele->type == 'D' && ele->data.ld >= 0)
				|| (ele->type == 'f' && ele->data.f >= 0.0))
		ele->pos = 1;
	if (ele->plus && ele->pos)
		ft_fill_out(str, "+", 1);
	if (ele->space && !ele->plus && ele->pos)
		ft_fill_out(str, " ", 1);
}

void			ft_flags_num(t_out *output, t_arg *ele)
{
	t_out	str;

	ft_init_out(&str);
	if (ele->hash && ((ele->type == 'o') || ele->type == 'O'
				|| (ele->format == 'u' && ele->data.u > 0)
				|| (ele->format == 'U' && ele->data.lu > 0)
				|| (ele->format == 'K' && ele->data.llu > 0)))
	{
		ft_fill_out(&str, "0", 1);
		if (ele->type != 'o' && ele->type != 'O')
		{
			ft_fill_out(&str, &ele->type, 1);
			ele->sharp = 1;
		}
	}
	ft_is_plus(&str, ele);
	ft_fill_out(output, str.out, str.len);
	ft_free_out(&str);
}
