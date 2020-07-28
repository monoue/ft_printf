#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

#define CTOI(c) c - '0'

typedef struct	s_fmt_info
{
	char	conversion;
	int	precision;
	int	minwidth;
	void	*value;
}		t_fmt_info;

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

int	ft_isconversion(char c)
{
	if (c == 'd' || c == 'x' || c == 's')
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

char	*ft_getfirstn(char *str, int len)
{
	char	*res;

	if (!str)
		return (NULL);
	res = ft_substr(str, 0, len);
	free(str);
	return (res);
}

char	*ft_prepend(char *str, char c, int len)
{
	if (len < 0)
		return (str);
	while (len--)
		str = ft_strjoin_free(ft_ctoa(c), str);
	return (str);
}

char	*ft_get_format(char *format)
{
	int	index;

	index = 1;
	while (format[index] == '.' || ft_isdigit(format[index]))
		index++;
	if (ft_isconversion(format[index]))
		index++;
	return (ft_substr(format, 0, index));
}

int	ft_isvalidate(char *target)
{
	if (!target || ft_strlen(target) < 2)
		return (0);
	return (ft_isconversion(target[ft_strlen(target) - 1]));
}

void		*ft_get_value(char conversion, va_list *arg_list)
{
	char	*tmp;

	if (conversion == 'd')
		return (ft_itoa((long)va_arg(*arg_list, int)));
	else if (conversion == 'x')
		return (ft_xtoa(va_arg(*arg_list, unsigned int)));
	else if (conversion == 's')
	{
		tmp = ft_strdup(va_arg(*arg_list, char *));
		if (!tmp)
			tmp = ft_strdup("(null)");
		return (tmp);
	}
	return (NULL);
}

t_fmt_info	*ft_generate_fi(char *target, va_list *arg_list)
{
	int		res;
	int		index;
	t_fmt_info	*fmt_info;

	fmt_info = malloc(sizeof(t_fmt_info) * 1);
	if (!fmt_info)
		return (NULL);
	fmt_info->conversion = target[ft_strlen(target) - 1];
	index = 1;
	res = -1;
	while (ft_isdigit(target[index]))
	{
		if (res == -1)
			res = 0;
		// res = res * 10 + target[index] - '0';
		res = res * 10 + CTOI(target[index]);
		index++;
	}
	fmt_info->minwidth = res;
	res = -1;
	if (target[index] == '.')
	{
		res = 0;
		index++;
		while (ft_isdigit(target[index]))
		{
			// res = res * 10 + target[index] - '0';
			res = res * 10 + CTOI(target[index]);
			index++;
		}
	}
	fmt_info->precision = res;
	fmt_info->value = ft_get_value(fmt_info->conversion, arg_list);
	return (fmt_info);
}

char	*ft_apply_precision(char conversion, int precision, char *new_target)
{
	if (precision == -1)
		return (new_target);
	if ((conversion == 'd' || conversion == 'x') && precision == 0 && new_target[0] == '0')
		return (ft_getfirstn(new_target, 0));
	if (conversion == 'd')
	{
		if (new_target[0] == '-' && ft_strlen(new_target) <= precision)
		{
			new_target[0] = '0';
			new_target = ft_prepend(new_target, '0', precision - ft_strlen(new_target) + 1);
			new_target[0] = '-';
		}
		else if (ft_strlen(new_target) < precision)
			new_target = ft_prepend(new_target, '0', precision - ft_strlen(new_target));
		return (new_target);
	}
	if (conversion == 'x' && ft_strlen(new_target) < precision)
		return (ft_prepend(new_target, '0', precision - ft_strlen(new_target)));
	if (conversion == 's' && ft_strlen(new_target) > precision)
		return (ft_getfirstn(new_target, precision));
	return (new_target);
}

int	ft_format(t_fmt_info *fmt_info)
{
	int	res;
	char	*new_target;

	new_target = ft_strdup(fmt_info->value);
	new_target = ft_apply_precision(fmt_info->conversion, fmt_info->precision, new_target);
	if (fmt_info->minwidth > ft_strlen(new_target))
		new_target = ft_prepend(new_target, ' ', fmt_info->minwidth - ft_strlen(new_target));
	res = ft_strlen(new_target);
	write(1, new_target, res);
	free(new_target);
	free(fmt_info->value);
	free(fmt_info);
	return (res);
}

void	ft_putchar_count_and_format_increment(const char **str, int *count)
{
	write(1, *str, 1);
	(*count)++;
	(*str)++;
}

int	ft_printf(const char *format, ...)
{
	int	cnt;
	char	*target;
	va_list	arg_list;

	va_start(arg_list, format);
	cnt = 0;
	while (format && *format)
	{
		if (*format != '%')
		{
			ft_putchar_count_and_format_increment(&format, &cnt);
			// write(1, format, 1);
			// cnt++;
			// format++;
		}
		else
		{
			target = ft_get_format((char *)format);
			if (ft_isvalidate(target))
				cnt += ft_format(ft_generate_fi(target, &arg_list));
			format += ft_strlen(target);
			free(target);
		}
	}
	va_end(arg_list);
	return (cnt);
}

#include <stdio.h>
int	main(void)
{
	int	ret;

	ret = ft_printf("%3.3d %3.3s %3.3x\n", 10, "ABC", 128);
	printf("%d\n", ret);
}
