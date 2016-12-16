/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:37:37 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/16 16:02:44 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_free_ele(t_arg **arg)
{
	if (arg && *arg)
	{
		if ((*arg)->flag)
		{
			free((*arg)->flag);
			(*arg)->flag = NULL;
		}
		free(*arg);
		*arg = NULL;
	}
}

void	ft_init_outp(t_outp *out)
{
	out->stocked = 0;
	out->stock = NULL;
	ft_bzero(out->out, BUFFSIZE);
	out->len = 0;
}

void	ft_free_outp(t_outp *out)
{
	if (out->stocked == 1)
		free(out->stock);
}

void	ft_init_out(t_out *out)
{
	out->out = NULL;
	out->len = 0;
}

void	ft_free_out(t_out *out)
{
	if (out && out->out)
	{
		free(out->out);
		out->out = NULL;
		out->len = 0;
	}
}
