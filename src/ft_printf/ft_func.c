/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 19:38:24 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/15 19:58:03 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_init_base(char type)
{
	int					base;

	base = 10;
	if (type == 'x' || type == 'X')
		base = 16;
	else if (type == 'o' || type == 'O')
		base = 8;
	else if (type == 'b')
		base = 2;
	return (base);
}

void			ft_nonspec(t_outp **output, t_out *tmp, t_arg *ele)
{
	char		c[2];

	c[1] = '\0';
	c[0] = ele->type;
	if (ele->pad != 0)
	{
		if (ele->pad > 0)
			ele->pad -= 1;
		else
			ele->pad += 1;
	}
	ft_pad(tmp, c, ele);
	if (tmp->out)
		ft_fill_outp(output, tmp->out, tmp->len);
}

static void		ft_point_b(t_outp **output, t_arg *ele, t_out *tmp, t_out *flag)
{
	t_out		prec;

	ft_init_out(&prec);
	if (ele->precision != -1)
	{
		ele->precision -= ele->len;
		while (ele->precision > 0)
		{
			ft_fill_out(&prec, "0", 1);
			ele->precision--;
		}
		ft_join_before(tmp, prec.out, prec.len);
	}
	if (ele->pad != 0)
	{
		ele->pad += (ele->pad > 0) ? -(flag->len) : flag->len;
		ft_pad(tmp, flag->out, ele);
	}
	else
		ft_fill_outp(output, flag->out, flag->len);
	ft_fill_outp(output, tmp->out, tmp->len);
	ft_free_out(&prec);
}

void			ft_point(unsigned long int nb, t_outp **output, t_out *tmp,
					t_arg *ele)
{
	t_out		flag;

	ft_init_out(&flag);
	ft_fill_out(&flag, "0x", 2);
	tmp->out = ft_itoa_base(nb, 16, 'x', &(ele->len));
	tmp->len += ele->len;
	if (*(tmp->out) == '0')
		ele->zero = 1;
	if (ele->precision == -1)
	{
		ele->padchar = ' ';
		if (ele->zero)
			ft_free_out(tmp);
	}
	ft_point_b(output, ele, tmp, &flag);
	ft_free_out(&flag);
}

void			ft_percent(t_outp **output, t_out *tmp, t_arg *ele)
{
	ft_fill_out(tmp, "%", 1);
	if (ele->pad != 0)
		ft_pad(tmp, 0, ele);
	ft_fill_outp(output, tmp->out, tmp->len);
}
