/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 12:18:32 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/16 14:53:16 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "g_col.h"

void		ft_find_modif(const char **str, char flag[200], char *modif)
{
	int		i;

	i = 0;
	*str += 1;
	while (**str != '\0' && (!ft_strchr("nfFdDiboOuUxXcsCSp%", **str)
				&& (ft_strchr(" *lzjh.+-#", **str) || ft_isdigit(**str))))
	{
		if (**str == 'l' || **str == 'z' || **str == 'j' || (**str == 'h'
				&& !ft_strchr(flag, 'j') && !ft_strchr(flag, 'z')
				&& !ft_strchr(flag, 'l')))
			*modif = **str;
		flag[i] = **str;
		*str += 1;
		i++;
	}
	flag[i] = '\0';
	if (ft_strstr(flag, "hh") && !ft_strchr(flag, 'j') && !ft_strchr(flag, 'z')
			&& !ft_strchr(flag, 'l'))
		*modif = 'H';
	else if (ft_strstr(flag, "ll"))
		*modif = 'L';
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
		else if (ft_strchr("uoxXb", ele->type))
			ele->format = 'U';
		else if (ele->type == 's' || ele->type == 'c')
		{
			ele->type = (ele->type == 's') ? 'S' : 'C';
			ele->format = (ele->type == 'C') ? 'C' : ele->format;
		}
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
