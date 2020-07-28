/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:07:49 by monoue            #+#    #+#             */
/*   Updated: 2020/07/28 17:20:15 by monoue           ###   ########.fr       */
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

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

char	*ft_substr(char	*str, int start, int len)
{
	int	size;
	int	index;
	char	*res;

	if (!str || start < 0 || len < 0)
		return (NULL);
	if (ft_strlen(str) <= start)
		return (NULL);
	size = (ft_strlen(str) < start + len) ? ft_strlen(str) - start : len;
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	index = 0;
	while (str[index + start] && index < len)
	{
		res[index] = str[index + start];
		index++;
	}
	res[index] = '\0';
	return (res);
}

char	*ft_ctoa(char c)
{
	char	*res;

	res = ft_strdup("0");
	if (!res)
		return (NULL);
	res[0] = c;
	return (res);
}

char	*ft_itoa(long num)
{
	if (num < 0)
		return (ft_strjoin_free(ft_ctoa('-'), ft_itoa(-num)));
	else if (num >= 10)
		return (ft_strjoin_free(ft_itoa(num / 10), ft_itoa(num % 10)));
	else
		return (ft_ctoa((char)(num + '0')));
}

char	*ft_xtoa(unsigned int num)
{
	if (num >= 16)
		return (ft_strjoin_free(ft_xtoa(num / 16), ft_xtoa(num % 16)));
	else
		return (ft_ctoa("0123456789abcdef"[num]));
}