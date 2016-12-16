/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ouput_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 18:32:31 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/16 11:20:26 by apetitje         ###   ########.fr       */
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

static t_outp	*ft_outcpy(t_outp **out, const char *s, int len)
{
	t_outp 	*new;
	char	*ptr;
	int		l;

	if ((*out)->len + len > BUFFSIZE)
	{
		ptr = (*out)->out + (*out)->len;
		l = BUFFSIZE - (*out)->len;
		ptr = ft_memcpy(ptr, s, l);
		s = s + l;
		len -= l;
		(*out)->len = BUFFSIZE;
		ft_init_outp(&new);
		(*out)->next = new;
		*out = (*out)->next;
	}
	while (len > BUFFSIZE)
	{
		ft_memcpy((*out)->out, s, BUFFSIZE);
		(*out)->len = BUFFSIZE;
		len -= BUFFSIZE;
		ft_init_outp(&new);
		s = s + len;
		(*out)->next = new;
		*out = (*out)->next;
	}
	ft_memcpy((*out)->out, s, len);
	(*out)->len = len;
	ft_init_outp(&new);
	(*out)->next = new;
	*out = (*out)->next;
	return (*out);
}

void		ft_fill_outp(t_outp **output, const char *s, int len)
{
	char	*ptr;
	char	*new_str;


	if (len > 0 && s)
	{
		if ((*output)->len > 0)
		{
			if (!(new_str = ft_memalloc(1 + len + (*output)->len)))
				exit(EXIT_FAILURE);
			new_str = ft_memcpy(new_str, (*output)->out, (*output)->len);
			ptr = new_str + (*output)->len;
			ptr = ft_memmove(ptr, s, len);
			ptr += len;
			*ptr = '\0';
			ft_outcpy(output, new_str, len + (*output)->len);
			free(new_str);
		}
		else
		{
			ft_outcpy(output, s, len);
		}
	}
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
			ptr = output->out + len;
			*ptr = '\0';
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

void	ft_init_outp(t_outp **out)
{
	if (!(*out = (t_outp *)malloc(sizeof(t_outp))))
			exit(EXIT_FAILURE);
	(*out)->next = NULL;
	ft_bzero((*out)->out, BUFFSIZE);
	(*out)->len = 0;
}

void	ft_free_outp(t_outp **out)
{
	t_outp *ptr;

	while (*out != NULL)
	{
		if ((*out)->len > 0)
		{
			ft_bzero((*out)->out, BUFFSIZE);
			(*out)->len = 0;
		}
		ptr = *out;
		*out = (*out)->next;
		free(ptr);
	}
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
