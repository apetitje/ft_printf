/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 19:43:10 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/13 21:16:30 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_find_pad(t_arg *ele, int i, va_list ap)
{
	if (ele->flag[i] == '-')
		ele->padleft = 1;
	else
		ele->pad = (ele->flag[i] == '*') ? va_arg(ap, int)
			: ft_atoi(ele->flag + i);
	if (ft_isdigit(ele->flag[i]))
	{
		while (ele->flag[i] && ft_isdigit(ele->flag[i]))
			i++;
		i--;
	}
	return (i);
}

static void		ft_padright(t_arg *ele, char *flag, t_out *pad, t_out *output)
{
	char	*ptr;

	ptr = NULL;
	if ((ele->padchar == ' ' || ele->type == 'Z') && flag && *flag)
		ft_fill_out(pad, flag, ft_strlen(flag));
	else if (flag && *flag)
		ft_join_before(pad, flag, ft_strlen(flag));
	else if (output->out && ft_strchr("fFdDi", ele->type)
			&& *(output->out) == '-' && ele->padchar == '0')
	{
		ft_join_before(pad, "-", 1);
		ptr = output->out;
		output->out = ft_strdup(output->out + 1);
		output->len -= 1;
		free(ptr);
	}
	if (pad->out)
		ft_join_before(output, pad->out, pad->len);
}

void			ft_pad(t_out *output, char *flag, t_arg *ele)
{
	t_out pad;

	ft_init_out(&pad);
	if (ele->padleft != 1)
		ele->padleft = (ele->pad < 0) ? 1 : 0;
	ele->pad = (ele->pad < 0) ? -(ele->pad) : ele->pad;
	ele->pad = ele->pad - output->len;
	if (ele->pad > 0)
	{
		if (!(pad.out = (char *)ft_memalloc(ele->pad + 1)))
			exit(EXIT_FAILURE);
		pad.out = ft_memset(pad.out, ele->padchar, ele->pad);
		pad.len = ele->pad;
	}
	if (ele->padleft == 1)
	{
		if (flag && *flag)
			ft_join_before(output, flag, ft_strlen(flag));
		if (pad.out)
			ft_fill_out(output, pad.out, pad.len);
	}
	else
		ft_padright(ele, flag, &pad, output);
	ft_free_out(&pad);
}
