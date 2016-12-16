/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ouput_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 18:32:31 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/16 20:01:01 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_fill_outp(t_outp *out, const char *s, int len)
{
	if (len > 0 && s)
	{
		if (out->len + len <= BUFFSIZE)
			ft_memcpy(out->out + out->len, s, len);
		else
		{
			out->stocked = 1;
			if (!out->stock)
			{
				if (!(out->stock = ft_memalloc(out->len + len + 1)))
					exit(EXIT_FAILURE);
				out->stock = ft_memcpy(out->stock, out->out, out->len);
			}
			else if (!(out->stock = ft_realloc(out->stock, 1 + len + out->len)))
				exit(EXIT_FAILURE);
			ft_memcpy(out->stock + out->len, s, len);
		}
	}
	out->len += len;
}

void	ft_fill_out(t_out *out, const char *format, int len)
{
	if (len > 0 && format)
	{
		if (out->len + len <= BUFFSIZE)
			ft_memcpy(out->out + out->len, format, len);
		else
		{
			if (out->stocked)
			{
				if (!(out->out = ft_realloc(out->out, 1 + len + out->len)))
					exit(EXIT_FAILURE);
			}
			else
			{
				if (!(out->out = ft_memalloc(out->len + len + 1)))
					exit(EXIT_FAILURE);
				out->out = ft_memcpy(out->out, out->out1, out->len);
			}
			ft_memcpy(out->out + out->len, format, len);
			out->stocked = 1;
		}
	}
	out->len += len;
}

void	ft_join_before(t_out *out, const char *s, int len)
{
	char	*new_str;
	int		nlen;

	if (len > 0)
	{
		if (!s)
			return ;
		else
		{
			if (!(new_str = ft_memalloc(out->len + len + 1)))
				exit(EXIT_FAILURE);
			new_str = ft_memcpy(new_str, s, len);
			ft_memcpy(new_str + len, out->out, out->len);
			nlen = out->len + len;
			ft_free_out(out);
			ft_fill_out(out, new_str, nlen);
			free(new_str);
		}
	}
}
