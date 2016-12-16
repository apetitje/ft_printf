/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:50:20 by apetitje          #+#    #+#             */
/*   Updated: 2016/12/16 13:18:34 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <wchar.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define NORM		"\x1B[0m"
# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[34m"
# define MAGENTA	"\x1B[35m"
# define CYAN		"\x1B[36m"
# define WHITE  	"\x1B[37m"

/*
** h = short int ;
** d = int;
** D = long int;
** L = long long int;
** y = unsigned short int;
** u = unsigned int;
** U = unsigned long int;
** K = unsigned long long int;
** c = char;
** s = char*;
** w = unsigned char;
** z = signed char;
** C = wchar_t;
** S = wchar_t*;
** f = double;
*/

# define BUFFSIZE			127

typedef struct				s_outp
{
	char					out[BUFFSIZE];
	int						stocked;
	char					*stock;
	int						len;
}							t_outp;

typedef struct				s_out
{
	int						len;
	char					*out;
}							t_out;

typedef struct				s_col
{
	char					str[20];
	int						len;
	char					*code;
	int						codelen;
}							t_col;

typedef struct				s_data
{
	int						d;
	unsigned int			u;
	unsigned long int		lu;
	unsigned long long int	llu;
	void					*p;
	long int				ld;
	wchar_t					lc;
	char					c;
	long long int			ll;
	unsigned char			uc;
	long double				f;
}							t_data;

typedef	struct				s_arg
{
	int						zero;
	char					type;
	char					*flag;
	char					format;
	struct s_data			data;
	char					modifier;
	int						pad;
	char					padchar;
	int						precision;
	int						len;
	int						padleft;
}							t_arg;

void						ft_fill_outp(t_outp *output, const char *s, int len);
void						ft_free_outp(t_outp *out);
void						ft_init_outp(t_outp *out);
int							ft_asprintf(char **strp, const char *format, ...);
void						ft_modifier(t_arg *ele);
void						ft_pad(t_out *output, char *flag, t_arg *ele);
void						ft_flags_all(t_arg *ele, va_list ap);
void						ft_flags_num(t_out *output, t_arg *ele);
int							ft_printf(const char *format, ...);
void						ft_percent(t_outp *output, t_out *tmp, t_arg *ele);
void						ft_alpha(t_outp *output, t_out *tmp, t_arg *ele);
void						ft_num(t_outp *output, t_out *tmp, t_arg *ele,
								int base);
void						ft_wide(t_outp *output, t_out *tmp, t_arg *ele);
void						ft_point(unsigned long int nb, t_outp *output,
								t_out *tmp, t_arg *ele);
void						ft_fill_out(t_out *output,
								const char *format, int len);
void						ft_init_out(t_out *out);
void						ft_free_out(t_out *out);
void						ft_join_before(t_out *out, const char *s, int len);
void						ft_free_ele(t_arg **arg);
void						ft_float(t_outp *output, t_out *tmp, t_arg *ele);
void						ft_process_format(t_outp *output, t_arg *ele);
void						ft_nonspec(t_outp *output, t_out *tmp, t_arg *ele);
void						ft_find_modif(const char **str, char flag[200],
								char *modif);
t_arg						*ft_arg(char type, char flag[200], char modifier);
int							ft_init_base(char type);
t_arg						*ft_print(t_outp *out, const char **str, va_list ap);
int							ft_find_pad(t_arg *ele, int i, va_list ap);
void						ft_color(t_outp *out, const char **str, int *len);

#endif
