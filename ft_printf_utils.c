/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:07:49 by monoue            #+#    #+#             */
/*   Updated: 2020/08/20 12:47:03 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(STDOUT_FILENO, &c, 1);
}

void	ft_putstr(char *str)
{
	write(STDOUT_FILENO, str, ft_strlen(str));
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;
	size_t			index;

	uc = (unsigned char)c;
	index = 0;
	while (s[index] != uc && s[index] != '\0')
		index++;
	if (s[index] == uc)
		return ((char *)(s + index));
	return (NULL);
}

bool	ft_isdigit(const unsigned int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}
