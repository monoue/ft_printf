/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_exam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 15:10:06 by monoue            #+#    #+#             */
/*   Updated: 2020/07/28 16:21:04 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

// #define NOT_SPECIFIED -1
#define CTOI(c) c - '0'

int	ft_ctoi(char c)
{
	return (c - '0');
}

typedef	struct	s_format_info
{
	char	conversion_c;
	int		min_width;
	int		precision;
	void	*value;
}				t_format_info;

int	ft_putchar_return_one(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_isdigit(char c)
{
	return ('0' <= c && c <= '9');
}

int	ft_isconversion_specifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'x');
}

char	*ft_strdup(char *str)
{
	int		index;
	char	*duplicated;

	if (!str)
		return (NULL);
	duplicated = malloc(ft_strlen(str) + 1);
	if (!duplicated)
		return (NULL);
	index = 0;
	while (str[index])
	{
		duplicated[index] = str[index];
		index++;
	}
	duplicated[index] = '\0';
	return (duplicated);
}

char	*ft_substr(char *str, int start, int len)
{
	int	size;
	int	index;
	char	*substring;

	if (!str || start < 0 || len < 0)
		return (NULL);
	if (ft_strlen(str) <= start)
		return (NULL);
	size = (ft_strlen(str) < start + len) ? ft_strlen(str) - start : len;
	substring = malloc(size + 1);
	if (!substring)
		return (NULL);
	index = 0;
	while (index < len && str[start + index])
	{
		substring[index] = str[start + index];
		index++;
	}
	substring[index] = '\0';
	return (substring);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_index;
	int		s2_index;
	char	*joined_str;

	joined_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined_str)
		return (NULL);
	s1_index = 0;
	while (s1 && s1[s1_index])
	{
		joined_str[s1_index] = s1[s1_index];
		s1_index++;
	}
	s2_index = 0;
	while (s2 && s2[s2_index])
	{
		joined_str[s1_index + s2_index] = s2[s2_index];
		s2_index++;
	}
	joined_str[s1_index + s2_index] = 0;
	return (joined_str);
}

char	*ft_strjoin_both_free(char *s1, char *s2)
{
	char	*joined_str;

	joined_str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined_str);
}

char	*ft_get_format(char *format)
{
	int	index;

	index = 1;

	// % 後は、まず . or 数字 はスキップし続ける。
	// while (format[index] == '.' || ft_isdigit(format[index]))

	while (format[index] && !ft_isconversion_specifier(format[index]))
		index++;
	// conversion である場合、１回だけ index 進める。
	if (ft_isconversion_specifier(format[index]))
		index++;
	// 最後、% から conversion_c までを返す
	return (ft_substr(format, 0, index));
}

int	ft_isvalid_format(char *str)
{
	size_t	slen;

	if (!str)
		return (0);
	slen = ft_strlen(str);
	if (slen < 2)
		return (0);
	return (ft_isconversion_specifier(str[slen - 1]));
}

int	ft_get_min_width(char *format_str)
{
	int	min_width;
	int	index;

	if (!ft_isdigit(format_str[index]))
		return (NOT_SPECIFIED);
	index = 1;
	min_width = 0;
	while (ft_isdigit(format_str[index]))
	{
		min_width = min_width * 10 + ft_ctoi(format_str[index]);
		// min_width = min_width * 10 + CTOI(format_str[index]);
		index++;
	}
	return (min_width);
}

int	ft_get_precision(char *format_str)
{
	int	precision;
	int	index;

	index = 1;
	while (format_str[index] && format_str[index] != '.')
		index++;
	if (!format_str[index])
		return (NOT_SPECIFIED);
	index++;
	precision = 0;
	while (ft_isdigit(format_str[index]))
	{
		precision = precision * 10 + ft_ctoi(format_str[index]);
		// precision = precision * 10 + CTOI(format_str[index]);
		index++;
	}
	return (precision);
}

char	*ft_ctoa(char c)
{
	char *res;

	res = ft_strdup("0");
	if (!res)
		return (NULL);
	res[0] = c;
	return (res);
}

char	*ft_itoa(long num)
{
	if (num < 0)
		return (ft_strjoin_both_free(ft_strdup("-"), ft_itoa(-num)));
	else if (num >= 10)
		return (ft_strjoin_both_free(ft_itoa(num / 10), ft_itoa(num % 10)));
	else
		return (ft_ctoa((char)(num + '0')));
}

char	*ft_xtoa(unsigned int num)
{
	if (num >= 16)
		return (ft_strjoin_both_free(ft_xtoa(num / 16), ft_xtoa(num % 16)));
	else
		return (ft_ctoa("0123456789abcdef"[num]));
}

char	*ft_stoa(char *str)
{
	if (!str)
		return (ft_strdup("(null)"));
	else
		return (ft_strdup(str));
}

void	*ft_get_value(char conversion_c, va_list *arg_list)
{
	if (conversion_c == 'd')
		return (ft_itoa((long)va_arg(*arg_list, int)));
	else if (conversion_c == 's')
		return (ft_stoa(va_arg(*arg_list, char *)));
	else if (conversion_c == 'x')
		return (ft_xtoa(va_arg(*arg_list, unsigned int)));
	return (NULL);
}

void	ft_putstr(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
}

t_format_info	*ft_gen_format_info(char *format_str, va_list *arg_list)
{
	t_format_info	*format_info;

	format_info = malloc(sizeof(t_format_info) * 1);
	format_info->conversion_c = format_str[ft_strlen(format_str) - 1];
	format_info->min_width = ft_get_min_width(format_str);
	format_info->precision = ft_get_precision(format_str);
	format_info->value = ft_get_value(format_info->conversion_c, arg_list);
	return (format_info);
}

char	*ft_getfirstn(char *str, int n)
{
	char *res;

	res = ft_substr(str, 0, n);
	free(str);
	return (res);
}

char	*ft_prepend(char *str, char c, int n)
{
	if (n < 1)
		return (str);
	while (n--)
		str = ft_strjoin_both_free(ft_ctoa(c), str);
	return (str);
}

char	*ft_apply_precision(char *str, int precision, char conversion_c)
{
	if (precision == NOT_SPECIFIED)
		return (str);
	if ((conversion_c == 'd' || conversion_c == 'x') && str[0] == '0' && !str[1] && precision == 0)
		return (ft_getfirstn(str, 0));
	if (conversion_c == 'd' && ft_strlen(str) <= precision && str[0] == '-')
	{
		str[0] = 0;
		str = ft_prepend(str, '0', precision - ft_strlen(str) + 1);
		str[0] = '-';
		return (str);
	}
	if (conversion_c == 'd' && ft_strlen(str) < precision && str[0] != '-')
		return (ft_prepend(str, '0', precision - ft_strlen(str)));
	if (conversion_c == 'x' && ft_strlen(str) < precision)
		return (ft_prepend(str, '0', precision - ft_strlen(str)));
	if (conversion_c == 's' && ft_strlen(str) > precision)
		return (ft_getfirstn(str, precision));
	return (str);
}

char	*ft_apply_minwidth(char *str, char min_width)
{
	if (min_width == NOT_SPECIFIED)
		return (str);
	if (ft_strlen(str) < min_width)
		return (ft_prepend(str, ' ', min_width - ft_strlen(str)));
	return (str);
}

void	free_format_info(t_format_info *format_info)
{
	free(format_info->value);
	free(format_info);
}

int	ft_format(t_format_info *format_info)
{
	int		len;
	char	*new_str;

	new_str = ft_strdup(format_info->value);
	new_str = ft_apply_precision(new_str, format_info->precision, format_info->conversion_c);
	new_str = ft_apply_minwidth(new_str, format_info->min_width);
	ft_putstr(new_str);
	len = ft_strlen(new_str);
	free(new_str);
	new_str = NULL;
	free_format_info(format_info);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	char	*format_str;
	va_list	arg_list;

	count = 0;
	va_start(arg_list, format);
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar_return_one(*format);
			count++;
			format++;
		}
		else
		{
			format_str = ft_get_format((char *)format);
			if (ft_isvalid_format(format_str))
				count += ft_format(ft_gen_format_info(format_str, &arg_list));
			format += ft_strlen(format_str);
			free(format_str);
		}
	}
	va_end(arg_list);
	return (count);
}

int main()
{
	ft_printf("str: %5.5s\nnum: %d\nhex: %x\n", "abcde", 123, 200);
}
