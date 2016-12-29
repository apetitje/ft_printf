/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 12:18:32 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/29 19:47:31 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "g_col.h"

char		ft_find_type(const char *str, char *modif, t_arg *ele, va_list ap)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 'h')
		{
			if (!ft_strchr("jzlL", *modif))
			{
				*modif = str[i];
				if (str[i - 1] && str[i - 1] == 'h')
					*modif = 'H';
			}
		}
		else if (ft_strchr("lzj", str[i]))
		{
			*modif = str[i];
			if (str[i] == 'l' && ((str[i - 1] && str[i - 1] == 'l')))
				*modif = 'L';
		}
		else if (str[i] == '#')
			ele->hash = 1;
		else if (str[i] == '+')
			ele->plus = 1;
		else if (str[i] == ' ')
			ele->space = 1;
		else if (str[i] == '-')
			ele->padleft = 1;
		else if (str[i] == '*')
		{
			if (i == 0 || str[i - 1] != '.')
				ele->pad = va_arg(ap, int);
			else
			{
				ele->precision = va_arg(ap, int);
				if (ele->precision == 0)
					ele->precision = -1;
			}
			ele->wild = 1;
		}
		else if (str[i] == '0')
		{
			if (i == 0 || ft_isdigit(str[i - 1]) == 0)
				ele->zero = 1;
		}
		else if (ft_isdigit(str[i]) && (i == 0 || str[i - 1] != '.'))
			i = ft_find_pad(ele, i, str);
		else if (str[i] == '.' && str + i + 1)
			i = ft_precision(ele, i, str);
		else
		{
			ele->type = str[i];
			return (i);
		}
	}
	ele->type = str[i];
	return (i);
}

t_arg		*ft_find_modif(const char **str, char *modif,
		va_list ap)
{
	t_arg	*ele;
	int		i;

	*str += 1;
	ele = ft_arg();
	i = ft_find_type(*str, modif, ele, ap);
	*str = *str + i;
	if (ele->type == '\0')
	{
		free(ele);
		return (NULL);
	}
	ele->modifier = *modif;
	ele->format = ele->type;
	ft_modifier(ele);
	if (ele->zero && (((ft_strchr("scSC%Z", ele->type) || ele->precision == 0) && !ele->padleft) || (ele->precision != 0 && ele->wild)))
		ele->padchar = '0';
	return (ele);
}

static void	ft_num_modif(t_arg *ele)
{
	if (ele->modifier == 'z')
	{
		if (ele->type == 'd' || ele->type == 'i')
			ele->type = 'L';
		else if (ft_strchr("uoxXb", ele->type))
			ele->format = 'U';
	}
	else if (ele->modifier == 'H')
	{
		if (ele->type == 'd' || ele->type == 'i')
			ele->type = 'z';
		else if (ft_strchr("uoxXb", ele->type))
			ele->format = 'w';
	}
	else if (ele->modifier == 'h')
	{
		if (ele->type == 'd' || ele->type == 'i')
			ele->format = 'h';
		else if (ft_strchr("uoxXb", ele->type))
			ele->format = 'y';
	}
}

void		ft_modifier(t_arg *ele)
{
	if (ele->modifier == 'l')
	{
		if (ele->type == 'd' || ele->type == 'i')
			ele->type = 'D';
		else if (ele->type == 's' || ele->type == 'c')
		{
			ele->type = (ele->type == 's') ? 'S' : 'C';
			ele->format = (ele->type == 'C') ? 'C' : ele->format;
		}
		else if (ft_strchr("uoxXb", ele->type))
			ele->format = 'U';
	}
	else if (ele->modifier == 'L')
	{
		if (ele->type == 'd' || ele->type == 'i')
			ele->type = 'L';
		else if (ft_strchr("uoxXb", ele->type))
			ele->format = 'K';
	}
	else if (ele->modifier == 'j' && (ele->type == 'd' || ele->type == 'i'))
		ele->type = 'D';
	else if (ele->modifier == 'j' && ft_strchr("uoxXb", ele->type))
		ele->format = 'U';
	ft_num_modif(ele);
}

void		ft_color(t_out *out, const char **str)
{
	int i;
	int	is_col;

	i = -1;
	is_col = 0;
	while (++i < 8)
	{
		if (!ft_strncmp(*str, g_coltab[i].str, g_coltab[i].len))
		{
			ft_fill_out(out, g_coltab[i].code, g_coltab[i].codelen);
			is_col = 1;
			break ;
		}
	}
	if (is_col)
	{
		while (**str != '}')
			*str += 1;
		*str += 1;
	}
}
