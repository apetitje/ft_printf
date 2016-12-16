/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:16:53 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/16 19:57:08 by apetitje         ###   ########.fr       */
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

static void		ft_make_num(t_arg *ele, t_out *tmp, t_out *flag, t_outp *out)
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
	ft_pad(tmp, flag->out, ele);
	ft_fill_outp(out, tmp->out, tmp->len);
}

void			ft_float(t_outp *output, t_out *tmp, t_arg *ele)
{
	t_out 		flag;
	char 		*str;

	ft_init_out(&flag);
	ft_flags_num(&flag, ele);
	if (!(ft_strchr(ele->flag, '#') && ele->precision == -1))
	{
		str = ft_dtoa(ele->data.f, (ele->precision > 0
					|| ele->precision == -1) ? ele->precision : 6, &(ele->len));
		ft_fill_out(tmp, str, ele->len);
	}
	else
	{
		str = ft_itoa((int)ele->data.f, &(ele->len));
		ft_fill_out(tmp, str, ele->len);
		ft_fill_out(tmp, ".", 1);
	}
	free(str);
	ft_make_num(ele, tmp, &flag, output);
	ft_free_out(&flag);
}

void			ft_num(t_outp *output, t_out *tmp, t_arg *ele, int base)
{
	t_out		flag;
	char		*str;

	str = NULL;
	ft_init_out(&flag);
	ft_flags_num(&flag, ele);
	if (ele->format == 'd')
		str = ft_itoa(ele->data.d, &(ele->len));
	else if (ele->format == 'D')
		str = ft_itoa(ele->data.ld, &(ele->len));
	else if (ele->format == 'U')
		str = ft_itoa_base(ele->data.lu, base,
					((base == 16) ? ele->type : 0), &(ele->len));
	else if (ele->format == 'u')
		str = ft_itoa_base(ele->data.u, base,
					((base == 16) ? ele->type : 0), &(ele->len));
	else if (ele->format == 'L')
		str = ft_itoa(ele->data.ll, &(ele->len));
	else if (ele->format == 'w')
		str = ft_itoa_base(ele->data.uc, base, ele->type,
					&(ele->len));
	else if (ele->format == 'K')
		str = ft_itoa_base(ele->data.llu, base, ele->type, &(ele->len));
	ft_fill_out(tmp, str, ele->len);
	ele->zero = (tmp->len > 0 && *(tmp->out) == '0') ? 1 : 0;
	ft_make_num(ele, tmp, &flag, output);
	if (str)
		free(str);
	ft_free_out(&flag);
}
