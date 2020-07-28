/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:57:30 by monoue            #+#    #+#             */
/*   Updated: 2020/07/28 17:18:45 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_isconversion(char c)
{
	if (c == 'd' || c == 'x' || c == 's')
		return (1);
	return (0);
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

void	ft_putchar_both_increment(const char **str, int *count)
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
			ft_putchar_both_increment(&format, &cnt);
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

// int	main(void)
// {
// 	int	ret;

// 	ret = ft_printf("%3.3d %3.3s %3.3x\n", 10, "ABC", 128);
// 	printf("%d\n", ret);
// }
