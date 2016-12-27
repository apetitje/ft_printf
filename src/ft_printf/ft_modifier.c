/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 12:18:32 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/27 15:57:36 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "g_col.h"

char		ft_find_type(const char **str, char flag[200], char *modif, int *i)
{
	if (**str == '\0')
		return (**str);
	if (ft_strchr("hlzj *.+-#0123456789", **str))
	{
		if (**str == 'h')
		{
			if (!ft_strchr("jzlL", *modif))
			{
				*modif = **str;
				if (*(*str - 1) && *(*str - 1) == 'h')
					*modif = 'H';
			}
		}
		if (ft_strchr("lzj", **str))
		{
			*modif = **str;
			if (**str == 'l' && ((*(*str - 1) && *(*str - 1) == 'l')))
				*modif = 'L';
		}
		flag[(*i)++] = *(*str)++;
		return (ft_find_type(str, flag, modif, i));
	}
	return (**str);
}

t_arg		*ft_find_modif(const char **str, char flag[200], char *modif,
		va_list ap)
{
	int		i;
	char	type;

	i = 0;
	*str += 1;
	type = ft_find_type(str, flag, modif, &i);
	flag[i] = '\0';
	return (ft_arg(type, flag, *modif, ap));
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
