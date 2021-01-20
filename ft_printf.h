/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 11:56:31 by monoue            #+#    #+#             */
/*   Updated: 2021/01/20 14:50:02 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <limits.h>
# include <stdbool.h>
# include "libft/libft.h"

# define CTOI(c)		c - '0'
# define NOT_SET		-1
# define SAFE_FREE(ptr)	{free(ptr);ptr = NULL;}

typedef struct	s_format_info
{
	int		min_width;
	int		precision;
	char	conv_c;
	bool	minus;
	bool	zero;
	bool	c_null;
	void	*value;
}				t_format_info;

/*
** each function has its own file
*/
int				put_result(t_format_info *info);
char			*cut_out_format(const char **format, va_list *ap);
void			init_format_info(t_format_info *info);
void			set_zero_minwidth_minus_prec(char *target, int *index,
													t_format_info *info);
void			apply_margin(char **new_target, int empty_width,
													t_format_info *info);

/*
** fill_with_zero.c
*/
void			fill_output_with_zero(char **str, int len);
void			fill_empty_with_zero(char **str, int len,
													t_format_info *info);

/*
** is.c
*/
bool			is_of_chars(const unsigned int c, int argc, ...);
bool			isconversion_c(const unsigned int c);

/*
** ft_printf_utils.c
*/
// void			ft_putchar(char c);
// void			ft_putstr(char *str);
// size_t			ft_strlen(const char *str);
// char			*ft_strchr(const char *s, int c);
// bool			ft_isdigit(const int c);

/*
** ft_printf_utils2.c
*/
// char			*ft_strdup(const char *original_s);
// char			*ft_strjoin_free_both(char *s1, char *s2);
// char			*ft_substr(char *original_s, int start, int len);

/*
** toa_malloc.c
*/
char			*ft_ctoa_malloc(unsigned int c);
char			*ft_utoa_malloc(unsigned int num);
char			*ft_itoa_malloc(long num);
char			*ft_xtoa_malloc(unsigned long long num,
												t_format_info *info);

int				ft_printf(const char *format, ...);

#endif
