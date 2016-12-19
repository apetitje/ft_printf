/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alpha.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:49:48 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/19 15:33:17 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_alpha(t_outp *output, t_out *tmp, t_arg *ele)
{
	char		*s;

	s = ele->data.p;
	if (ele->type == 'c')
		ft_fill_out(tmp, &(ele->data.c), 1);
	else if (ele->type == 's' && ele->precision != -1)
	{
		if (s)
		{
			ele->len = ft_strlen(s);
			if (ele->len > ele->precision && ele->precision > 0)
				ele->len = ele->precision;
			ft_fill_out(tmp, s, ele->len);
		}
		else
			ft_fill_out(tmp, "(null)", 6);
	}
	if (ele->pad != 0)
		ft_pad(tmp, 0, ele);
	ft_fill_outp(output, tmp->out, tmp->len);
	ft_free_out(tmp);
}
