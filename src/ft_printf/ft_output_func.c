/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ouput_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 18:32:31 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/16 13:20:00 by apetitje         ###   ########.fr       */
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

void		ft_fill_outp(t_outp *output, const char *s, int len)
{
	char	*ptr;

	if (len > 0 && s)
	{
		if (output->len + len <= BUFFSIZE)
		{
			if (output->len > 0)
			{
				ptr = output->out + output->len;
				ptr = ft_memmove(ptr, s, len);
				ptr += len;
				*ptr = '\0';
			}
			else
				ft_memcpy(output, s, len);
		}
		else
		{
			output->stocked = 1;
			if (output->stock)
			{
				if (!(output->stock = ft_realloc(output->stock, 1 + len + output->len)))
					exit(EXIT_FAILURE);
				ptr = output->stock + output->len;
				ptr = ft_memmove(ptr, s, len);
				ptr += len;
				*ptr = '\0';
			}
			else
			{
				if (!(output->stock = ft_memalloc(len + 1)))
					exit(EXIT_FAILURE);
				output->stock = ft_memmove(output->stock, s, len);
			}
		}
	}
	output->len += len;
}

void	ft_fill_out(t_out *output, const char *format, int len)
{
	char	*ptr;

	if (len > 0 && format)
	{
		if (output->out)
		{
			if (!(output->out = ft_realloc(output->out, 1 + len + output->len)))
				exit(EXIT_FAILURE);
			ptr = output->out + output->len;
			ptr = ft_memmove(ptr, format, len);
			ptr += len;
			*ptr = '\0';
		}
		else
		{
			if (!(output->out = ft_memalloc(len + 1)))
				exit(EXIT_FAILURE);
			output->out = ft_memmove(output->out, format, len);
		}
	}
	output->len += len;
}

void	ft_join_before(t_out *out, const char *s, int len)
{
	char	*ptr;
	char	*new_str;

	if (!s)
		return ;
	else if (!out->out)
		out->out = ft_strdup(s);
	else
	{
		if (!(new_str = ft_memalloc(out->len + len + 1)))
			exit(EXIT_FAILURE);
		new_str = ft_memcpy(new_str, s, len);
		ptr = new_str + len;
		ptr = ft_memcpy(ptr, out->out, out->len);
		ptr += out->len;
		*ptr = '\0';
		free(out->out);
		out->out = new_str;
	}
	out->len += len;
}

void	ft_init_outp(t_outp *out)
{
	out->stocked = 0;
	ft_bzero(out->out, BUFFSIZE);
	out->len = 0;
}

void	ft_free_outp(t_outp *out)
{
	if (out->len > 0)
	{
		ft_bzero(out->out, BUFFSIZE);
		out->len = 0;
	}
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
