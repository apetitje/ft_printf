/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:51:45 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/19 16:35:15 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_end(char **strp, t_outp *out, t_arg **ele, va_list ap)
{
	if (!(*strp = ft_memalloc(out->len + 1)))
		exit(EXIT_FAILURE);
	if (!out->stocked)
		*strp = ft_memmove(*strp, out->out, out->len);
	else
		*strp = ft_memmove(*strp, out->stock, out->len);
	ft_free_ele(ele);
	ft_free_outp(out);
	va_end(ap);
	return (out->len);
}

int				ft_asprintf(char **strp, const char *format, ...)
{
	t_arg		*ele;
	va_list		ap;
	int			i;
	t_outp		output;

	i = 0;
	ft_init_outp(&output);
	va_start(ap, format);
	while (*format || *format == '\0')
	{
		ele = ft_print(&output, &format, ap);
		if (ele->type == '\0')
			return (ft_end(strp, &output, &ele, ap));
		ft_process_format(&output, ele);
		++format;
		ft_free_ele(&ele);
	}
	va_end(ap);
	return (0);
}
