/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:07:49 by monoue            #+#    #+#             */
/*   Updated: 2020/07/31 14:09:01 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(char *str)
{
	int	index;

	if (!str)
		return (0);
	index = 0;
	while (str[index])
		index++;
	return (index);
}

int	ft_isdigit(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

char	*ft_strdup(char *str)
{
	int	index;
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

// char	*ft_strdup_c(char c)
// {
// 	char	*res;

// 	if (!c)
// 		return (NULL);
// 	res = malloc(2);
// 	if (!res)
// 		return (NULL);
// 	res[0] = c;
// 	res[1] = '\0';
// 	return (res);
// }

char	*ft_strjoin(char *s1, char *s2)
{
	int	s1_index;
	int	s2_index;
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
	s1 = NULL;
	free(s1);
	s2 = NULL;
	free(s2);
	return (res);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*p;
	// size_t	srclen;
	int	srclen;
	// int	minlen;
	int	minlen;
	// int	i;
	int	i;

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

// char	*ft_substr(char	*str, int start, int len)
// {
// 	int	size;
// 	int	index;
// 	char	*res;

// 	if (!str || start < 0 || len < 0)
// 		return (NULL);
// 	if (ft_strlen(str) <= start)
// 		return (NULL);
// 	size = (ft_strlen(str) < start + len) ? ft_strlen(str) - start : len;
// 	res = malloc(size + 1);
// 	if (!res)
// 		return (NULL);
// 	index = 0;
// 	while (str[index + start] && index < len)
// 	{
// 		res[index] = str[index + start];
// 		index++;
// 	}
// 	res[index] = '\0';
// 	return (res);
// }

// char	*ft_ctoa(char c)
char	*ft_ctoa(unsigned int c)
{
	char	*res;

// ここから
	if (c == 0)
		return (NULL);
// ここまで
	res = ft_strdup("0");
	if (!res)
		return (NULL);
	res[0] = c;
	return (res);
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

char	*ft_xtoa(unsigned int num, t_format_info *format_info)
{
	if (num >= 16)
		return (ft_strjoin_free_both(ft_xtoa(num / 16, format_info), ft_xtoa(num % 16, format_info)));
	else if (format_info->conversion_c == 'x')
		return (ft_ctoa("0123456789abcdef"[num]));
	else
		return (ft_ctoa("0123456789ABCDEF"[num]));
}