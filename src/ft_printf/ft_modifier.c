/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 12:18:32 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/19 15:29:06 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "g_col.h"

char		ft_find_type(const char **str, char flag[200], char *modif, int *i)
{
	if (**str == '\0')
		return (**str);
	if (**str == 'h')
	{
		if (*modif != 'j' && *modif != 'z' && *modif != 'l' && *modif != 'L')
		{
			*modif = **str;
			if (*(*str - 1) && *(*str - 1) == 'h')
				*modif = 'H';
		}
		flag[*i] = **str;
		*str += 1;
		*i += 1;
		return (ft_find_type(str, flag, modif, i));
	}
	if (**str == 'l' || **str == 'z' || **str == 'j')
	{
		*modif = **str;
		if (**str == 'l' && ((*(*str - 1) && *(*str - 1) == 'l')))
			*modif = 'L';
		flag[*i] = **str;
		*str += 1;
		*i += 1;
		return (ft_find_type(str, flag, modif, i));
	}
	if (**str == ' ' || **str == '*' || **str == '.' || **str == '+' || **str == '-' || **str == '#' || (**str >= '0' && **str <= '9'))
	{
		flag[*i] = **str;
		*str += 1;
		*i += 1;
		return (ft_find_type(str, flag, modif, i));
	}
	return (**str);
}

t_arg		*ft_find_modif(const char **str, char flag[200], char *modif)
{
	int		i;
	char	type;

	i = 0;
	*str += 1;
	type = ft_find_type(str, flag, modif, &i);
	flag[i] = '\0';
	return (ft_arg(type, flag, *modif));
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

void		ft_color(t_outp *out, const char **str)
{
	int i;
	int	is_col;

	i = -1;
	is_col = 0;
	while (++i < 8)
	{
		if (!ft_strncmp(*str, g_coltab[i].str, g_coltab[i].len))
		{
			ft_fill_outp(out, g_coltab[i].code, g_coltab[i].codelen);
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
