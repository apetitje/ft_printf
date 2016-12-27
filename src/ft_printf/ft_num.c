/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:16:53 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 12:43:59 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_prec_num(t_arg *ele, t_out *tmp, t_out *flag)
{
	char		*ptr;
	t_out		prec;
	int 		len;

	ft_init_out(&prec);
	if (tmp->len > 0 && *(tmp->out) == '-')
	{
		ft_fill_out(&prec, "-", 1);
		len = tmp->len - 1;
		ptr = ft_strndup(tmp->out + 1, len);
		ft_free_out(tmp);
		ft_fill_out(tmp, ptr, len);
		free(ptr);
		ele->precision += 1;
	}
	ele->precision -= ele->len;
	if (flag->len > 0 && ft_strcmp(flag->out, "0x") != 0 &&
			ft_strcmp(flag->out, " ") != 0 && ft_strcmp(flag->out, "+") != 0)
		ele->precision -= flag->len;
	while (ele->precision > 0)
	{
		ft_fill_out(&prec, "0", 1);
		ele->precision--;
	}
	ft_join_before(tmp, prec.out, prec.len);
	ft_free_out(&prec);
}

static void		ft_make_num(t_arg *ele, t_out *tmp, t_out *flag, t_out *out)
{
	if (ele->precision != -1)
		ft_prec_num(ele, tmp, flag);
	else if (flag->len == 0 || (ele->type != 'o' && ele->type != 'O'))
	{
		ele->padchar = ' ';
		if (ele->zero)
			ft_free_out(tmp);
	}
	if (ele->pad != 0)
	{
		if (ele->pad > 0)
			ele->pad -= flag->len;
		else
			ele->pad += flag->len;
	}
	if (ele->zero && (flag->len > 0 && *(flag->out) != '+' && *(flag->out) != ' '))
		ft_free_out(flag);
	ft_pad(tmp, ((flag->len > 0) ? flag->out : 0), ele);
	ft_fill_out(out, tmp->out, tmp->len);
}

void			ft_float(t_out *output, t_out *tmp, t_arg *ele)
{
	t_out 		flag;

	ft_init_out(&flag);
	ft_flags_num(&flag, ele);
	if (!(ft_strchr(ele->flag, '#') && ele->precision == -1))
	{
		ft_dtoa(ele->data.f, (ele->precision > 0
					|| ele->precision == -1) ? ele->precision : 6, ele, tmp);
	}
	else
	{
		ft_itoa((int)ele->data.f, ele, tmp);
		ft_fill_out(tmp, ".", 1);
	}
	ft_make_num(ele, tmp, &flag, output);
	ft_free_out(&flag);
	ft_free_out(tmp);
}

void			ft_num(t_out *output, t_out *tmp, t_arg *ele)
{
	t_out		flag;

	ft_init_out(&flag);
	ft_flags_num(&flag, ele);
	if (ele->format == 'd')
		ft_itoa(ele->data.d, ele, tmp);
	else if (ele->format == 'D')
		ft_itoa(ele->data.ld, ele, tmp);
	else if (ele->format == 'L')
		ft_itoa(ele->data.ll, ele, tmp);
	else if (ele->format == 'U')
		ft_itoa_base(ele->data.lu, ele, tmp);
	else if (ele->format == 'u')
		ft_itoa_base(ele->data.u, ele, tmp);
	else if (ele->format == 'w')
		ft_itoa_base(ele->data.uc, ele, tmp);
	else if (ele->format == 'K')
		 ft_itoa_base(ele->data.llu, ele, tmp);
	ele->zero = (tmp->len > 0 && *(tmp->out) == '0') ? 1 : 0;
	ft_make_num(ele, tmp, &flag, output);
	ft_free_out(&flag);
	ft_free_out(tmp);
}
