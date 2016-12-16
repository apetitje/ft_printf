/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:51:45 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/16 11:20:51 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


static void		ft_init_arg(t_arg *new_ele)
{
	new_ele->zero = 0;
	new_ele->precision = 0;
	new_ele->padleft = 0;
	new_ele->pad = 0;
	new_ele->len = 0;
	new_ele->padchar = ' ';
}

t_arg			*ft_arg(char type, char flag[200], char modifier)
{
	t_arg		*new_ele;

	if (!(new_ele = malloc(sizeof(t_arg))))
		exit(EXIT_FAILURE);
	ft_init_arg(new_ele);
	new_ele->type = type;
	new_ele->modifier = modifier;
	new_ele->format = type;
	new_ele->flag = ft_strdup(flag);
	ft_modifier(new_ele);
	return (new_ele);
}

static int		ft_end(t_outp *out, t_arg **ele, va_list ap)
{
	int			len;
	t_outp		*ptr;
	char 		*str;
	char		*str_ptr;

	len = 0;
	str = ft_memalloc(1);
	while (out != NULL)
	{
	//	printf("str = %s, len = %d, out->len = %d\n", str, len, out->len);
		if (!(str = ft_realloc(str, out->len + len + 1)))
			exit(EXIT_FAILURE);
	//	printf("str = %s, len = %d, out->len = %d\n", str, len, out->len);
		str_ptr = str + len;
	//	printf("str_ptr = %s\n", str_ptr);
		str_ptr = ft_memcpy(str_ptr, out->out, out->len);
	//	printf("str_ptr = %s\n", str_ptr);
		str[out->len + len] = '\0';
		len += out->len;
	//	printf("str = %s, len = %d, out->len = %d\n", str, len, out->len);
		ptr = out;
		out = out->next;
		free(ptr);
	}
	write(1, str, len);
	ft_free_ele(ele);
	free(str);
	va_end(ap);
	return (len);
}

int				ft_printf(const char *format, ...)
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
			return (ft_end(begin, &ele, ap));
		if (ele->type != 'n')
			ft_process_format(&output, ele);
		format++;
		ft_free_ele(&ele);
	}
	va_end(ap);
	return (0);
}
