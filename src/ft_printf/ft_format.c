/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 19:14:06 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/16 15:16:51 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_format_u(va_list ap, t_arg *ele)
{
	if (ft_strchr("uoxXb", ele->type))
	{
		if (ele->format == 'U')
			ele->data.lu = va_arg(ap, unsigned long int);
		else if (ele->format == 'K')
			ele->data.llu = va_arg(ap, unsigned long long int);
		else if (ele->format == 'w')
			ele->data.uc = (unsigned char)va_arg(ap, int);
		else
		{
			ele->data.u = va_arg(ap, unsigned int);
			if (ele->format == 'y')
				ele->data.u = (unsigned short)ele->data.u;
			ele->format = 'u';
		}
	}
	else if (ele->type == 'f' || ele->type == 'F')
		ele->data.f = va_arg(ap, double);
	else if (ele->type == 'O' || ele->type == 'U')
	{
		ele->data.lu = va_arg(ap, unsigned long int);
		ele->format = 'U';
	}
}

static void		ft_format_alpha(va_list ap, t_arg *ele)
{
	if (ele->type == 'c')
	{
		ele->data.c = (char)va_arg(ap, int);
		ele->format = 'c';
	}
	else if (ele->type == 'C')
		ele->data.lc = (wchar_t)va_arg(ap, wint_t);
	else if (ele->type == 'p' || ele->type == 's' || ele->type == 'S')
	{
		ele->format = 'p';
		if (ele->type == 's')
			ele->data.p = va_arg(ap, char *);
		else if (ele->type == 'S')
			ele->data.p = va_arg(ap, wchar_t *);
		else if (ele->type == 'p')
			ele->data.p = va_arg(ap, void *);
	}
}

static void		ft_format(t_arg *ele, va_list ap)
{
	if (ele->type == 'd' || ele->type == 'i')
	{
		ele->data.d = va_arg(ap, int);
		if (ele->format == 'h')
			ele->data.d = (short)ele->data.d;
		ele->format = 'd';
	}
	else if (ele->type == 'z')
	{
		ele->data.d = (signed char)va_arg(ap, int);
		ele->format = 'd';
	}
	else if (ele->type == 'D')
	{
		ele->data.ld = va_arg(ap, long int);
		ele->format = 'D';
	}
	else if (ele->type == 'L')
	{
		ele->data.ll = (long long int)va_arg(ap, long int);
		ele->format = 'L';
	}
	ft_format_u(ap, ele);
	ft_format_alpha(ap, ele);
}

void			ft_process_format(t_outp *output, t_arg *ele)
{
	unsigned long int	nb;
	int					base;
	t_out				tmp;

	base = ft_init_base(ele->type);
	ft_init_out(&tmp);
	if (ele->type == 'p')
		nb = (unsigned long int)(ele->data.p);
	if (ele->type == 'C')
		ele->len = 1;
	if (ft_strchr("hydDuULwK", ele->format))
		ft_num(output, &tmp, ele, base);
	else if (ele->type == 'f' || ele->type == 'F')
		ft_float(output, &tmp, ele);
	else if (ele->format == 'c' || ele->type == 's')
		ft_alpha(output, &tmp, ele);
	else if (ele->type == 'C' || ele->type == 'S')
		ft_wide(output, &tmp, ele);
	else if (ele->type == 'p')
		ft_point(nb, output, &tmp, ele);
	else if (ele->type == '%')
		ft_percent(output, &tmp, ele);
	else
		ft_nonspec(output, &tmp, ele);
	ft_free_out(&tmp);
}

t_arg			*ft_print(t_outp *out, const char **str, va_list ap)
{
	t_arg	*ele;
	char	flag[200];
	char	modifier;

	modifier = 0;
	ft_bzero(flag, 200);
	while (**str && **str != '%')
	{
		if (**str == '{')
			ft_color(out, str);
		ft_fill_outp(out, *str, 1);
		*str += 1;
	}
	if (**str != '\0')
		ft_find_modif(str, flag, &modifier);
	ele = ft_arg(**str, flag, modifier);
	ft_flags_all(ele, ap);
	if (ele->type == 'n')
		*(va_arg(ap, int *)) = out->len;
	else
		ft_format(ele, ap);
	return (ele);
}
