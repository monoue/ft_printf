/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 11:56:31 by monoue            #+#    #+#             */
/*   Updated: 2020/07/29 07:35:41 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <limits.h>

# define CTOI(c) c - '0'
# define NOT_SPECIFIED -1

typedef struct	s_format_info
{
	char	conversion_c;
	int		precision;
	int		min_width;
	void	*value;
}				t_format_info;

int	ft_strlen(char *str);
int	ft_isdigit(char c);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_free_both(char *s1, char *s2);
char	*ft_substr(char	*str, int start, int len);
char	*ft_ctoa(char c);
char	*ft_itoa(long num);
char	*ft_xtoa(unsigned int num);

#endif
