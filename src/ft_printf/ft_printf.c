/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:51:45 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 11:45:20 by apetitje         ###   ########.fr       */
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

t_arg			*ft_arg(char type, char flag[200], char modifier, va_list ap)
{
	t_arg		*new_ele;

	if (type == '\0')
		return (NULL);
	if (!(new_ele = malloc(sizeof(t_arg))))
		exit(EXIT_FAILURE);
	ft_init_arg(new_ele);
	new_ele->type = type;
	new_ele->modifier = modifier;
	new_ele->format = type;
	new_ele->flag = ft_strdup(flag);
	ft_modifier(new_ele);
	ft_flags_all(new_ele, ap);
	return (new_ele);
}

static int		ft_end(t_out *out, t_arg **ele, va_list ap)
{
	int		len;

	len = out->len;
	if (!out->stocked)
		write(1, out->out1, out->len);
	else
		write(1, out->out, out->len);
	ft_free_ele(ele);
	ft_free_out(out);
	va_end(ap);
	return (len);
}

int				ft_printf(const char *format, ...)
{
	t_arg		*ele;
	va_list		ap;
	int			i;
	t_out		output;

	i = 0;
	ft_init_out(&output);
	va_start(ap, format);
	while (*format || *format == '\0')
	{
		if ((ele = ft_print(&output, &format, ap)) == NULL)
			return (ft_end(&output, &ele, ap));
		if (ele->type != 'n')
			ft_process_format(&output, ele);
		++format;
		ft_free_ele(&ele);
	}
	va_end(ap);
	return (0);
}
