/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:51:45 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/15 19:03:26 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_end(char **strp, t_outp *out, t_arg **ele, va_list ap)
{
	int			len;
	t_outp		*ptr;
	char 		*str;
	char		*str_ptr;

	len = 0;
	while (out != NULL)
	{
		str = ft_realloc(str, len + 1);
		str_ptr = str + len;
		str_ptr = ft_memcpy(str, out->out, out->len);
		len += out->len;
		str[len] = '\0';
		ptr = out;
		out = out->next;
		free(ptr);
	}
	*strp = str;
	ft_free_ele(ele);
	ft_free_outp(&out);
	va_end(ap);
	return (len);
}

int				ft_asprintf(char **strp, const char *format, ...)
{
	t_arg		*ele;
	va_list		ap;
	int			i;
	t_outp		*output;
	t_outp		*begin;

	i = 0;
	ft_init_outp(&output);
	begin = output;
	va_start(ap, format);
	while (*format || *format == '\0')
	{
		ele = ft_print(&output, &format, ap);
		if (ele->type == '\0')
			return (ft_end(strp, begin, &ele, ap));
		ft_process_format(&output, ele);
		format++;
		ft_free_ele(&ele);
	}
	va_end(ap);
	return (0);
}
