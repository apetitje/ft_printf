/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 20:50:12 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/19 18:11:21 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_precision(t_arg *ele, int i, va_list ap)
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
	else if (ele->flag[i + 1] == '*')
	{
		ele->precision = va_arg(ap, int);
		if (ele->precision == 0)
			ele->precision = -1;
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
		if (ele->flag[i] == '0' && (i == 0 || ft_isdigit(ele->flag[i - 1]) == 0)
			&& (((ft_strchr("scSC%Z", ele->type) || !ft_strchr(ele->flag, '.'))
				&& (!ft_strchr(ele->flag, '-'))) || (ft_strchr(ele->flag, '.')
					&& ft_strchr(ele->flag, '*'))))
			ele->padchar = '0';
		if ((ele->flag[i] == '-' || ft_isdigit(ele->flag[i]) || ele->flag[i] == '*')
				&& ele->flag[i] != '0' && (i == 0 || ele->flag[i - 1] != '.'))
			i = ft_find_pad(ele, i, ap);
		if (ele->flag[i] == '.' && ele->flag + i + 1)
			i = ft_precision(ele, i, ap);
	}
}

static void		ft_is_plus(t_out *str, t_arg *ele, int i, int *is_plus)
{
	if (ele->flag[i] == '+' && !*is_plus
			&& (((ele->type == 'i' || ele->type == 'd') && ele->data.d >= 0)
				|| (ele->type == 'D' && ele->data.ld >= 0)
				|| (ele->type == 'f' && ele->data.f >= 0.0)))
	{
		ft_fill_out(str, "+", 1);
		*is_plus = 1;
	}
	if (ele->flag[i] == ' ' && !(ft_strchr(ele->flag, '+'))
			&& (((ele->type == 'i' || ele->type == 'd') && ele->data.d >= 0)
				|| (ele->type == 'D' && ele->data.ld >= 0)
				|| (ele->type == 'f' && ele->data.f >= 0.0)))
		ft_fill_out(str, " ", 1);
}

void			ft_flags_num(t_out *output, t_arg *ele)
{
	int		i;
	t_out	str;
	int		is_plus;

	i = 0;
	ft_init_out(&str);
	is_plus = 0;
	while (ele->flag[i])
	{
		if (ele->flag[i] == '#' && ((ele->type == 'o') || ele->type == 'O'
				|| (ele->format == 'u' && ele->data.u > 0)
				|| (ele->format == 'U' && ele->data.lu > 0)
				|| (ele->format == 'K' && ele->data.llu > 0)))
		{
			ft_fill_out(&str, "0", 1);
			if (ele->type != 'o' && ele->type != 'O')
				ft_fill_out(&str, &ele->type, 1);
		}
		ft_is_plus(&str, ele, i, &is_plus);
		++i;
	}
	ft_fill_out(output, str.out, str.len);
	ft_free_out(&str);
}
