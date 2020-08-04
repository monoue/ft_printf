/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:07:49 by monoue            #+#    #+#             */
/*   Updated: 2020/08/04 14:23:00 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strlen(char *str)
{
	int	index;

	if (!str)
		return (0);
	index = 0;
	while (str[index])
		index++;
	return (index);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((int)((unsigned char)*s1 - (unsigned char)*s2));
}

int		ft_isdigit(char c)
{
	return ('0' <= c && c <= '9');
}

int		ft_isconversion_c(char c)
{
	return (c == 'c' || c == 'd' || c == 'i' || c == 'x' || c == 'X' || c == 's' || c == 'u' || c == 'p' || c == '%');
}

int		ft_isflag(char c)
{
	return (c == '-' || c == '0' || c == '.' || c == '*');
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putchar_increment_both(const char **str, int *count)
{
	ft_putchar((char)**str);
	(*count)++;
	(*str)++;
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_putstr_n(char *str, int len)
{
	int	index;

	index = 0;
	while (index < len)
	{
		if (str[index] == '1')
			ft_putchar('\0');
		else
			ft_putchar(str[index]);
		index++;
	}
}

char	*ft_strdup(char *str)
{
	int		index;
	char	*res;

	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	index = 0;
	while (str[index])
	{
		res[index] = str[index];
		index++;
	}
	res[index] = 0;
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_index;
	int		s2_index;
	char	*res;

	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	s1_index = 0;
	while (s1 && s1[s1_index])
	{
		res[s1_index] = s1[s1_index];
		s1_index++;
	}
	s2_index = 0;
	while (s2 && s2[s2_index])
	{
		res[s1_index + s2_index] = s2[s2_index];
		s2_index++;
	}
	res[s1_index + s2_index] = 0;
	return (res);
}

char	*ft_strjoin_free_both(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	SAFE_FREE(s1);
	SAFE_FREE(s2);
	return (res);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*p;
	int		srclen;
	int		minlen;
	int		i;

	if (s == NULL)
		return (NULL);
	srclen = ft_strlen(s);
	if (start > srclen)
		return (ft_strdup(""));
	minlen = MIN(srclen - start, len);
	p = malloc(sizeof(*p) * (minlen + 1));
	if (p == NULL)
		return (NULL);
	s += start;
	i = 0;
	while (minlen-- > 0)
		p[i++] = *s++;
	p[i] = '\0';
	return (p);
}

char	*ft_ctoa(unsigned int c)
{
	char	*res;

	res = ft_strdup("0");
	if (!res)
		return (NULL);
	res[0] = c;
	return (res);
}

char	*ft_utoa(unsigned int num)
{
	if (num >= 10)
		return (ft_strjoin_free_both(ft_utoa(num / 10), ft_utoa(num % 10)));
	else
		return (ft_ctoa((char)(num + '0')));
}

char	*ft_itoa(long num)
{
	if (num < 0)
		return (ft_strjoin_free_both(ft_ctoa('-'), ft_itoa(-num)));
	else if (num >= 10)
		return (ft_strjoin_free_both(ft_itoa(num / 10), ft_itoa(num % 10)));
	else
		return (ft_ctoa((char)(num + '0')));
}

char	*ft_xtoa(size_t num, t_format_info *format_info)
{
	if (num >= 16)
		return (ft_strjoin_free_both(ft_xtoa(num / 16, format_info), ft_xtoa(num % 16, format_info)));
	else if (format_info->conversion_c == 'X')
		return (ft_ctoa("0123456789ABCDEF"[num]));
	else
		return (ft_ctoa("0123456789abcdef"[num]));
}