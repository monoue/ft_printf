/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:57:30 by monoue            #+#    #+#             */
/*   Updated: 2020/07/29 16:15:22 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_isconversion_c(char c)
{
	return (c == 'c' || c == 'd' || c == 'i' || c == 'x' || c == 'X' || c == 's');
}

int	ft_isflag(char c)
{
	return (c == '-' || c == '0' || c == '.' || c == '*');
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

char	*ft_fill_output(char *str, char c, int len)
{
	if (len < 0)
		return (str);
	while (len--)
		str = ft_strjoin_free_both(ft_ctoa(c), str);
	return (str);
}

char	*ft_get_format(char *format)
{
	int	index;

	index = 1;
	while (ft_isflag(format[index] )|| ft_isdigit(format[index]))
		index++;
	if (ft_isconversion_c(format[index]))
		index++;
	return (ft_substr(format, 0, index));
}

int	ft_isvalid_format(char *target)
{
	if (!target || ft_strlen(target) < 2)
		return (0);
	return (ft_isconversion_c(target[ft_strlen(target) - 1]));
}

void		*ft_get_value(char conversion_c, va_list *arg_list)
{
	char	*tmp;

	if (conversion_c == 'd' || conversion_c == 'i')
		return (ft_itoa((long)va_arg(*arg_list, int)));
	else if (conversion_c == 'x' || conversion_c == 'X')
		return (ft_xtoa(va_arg(*arg_list, unsigned int), conversion_c));
	else if (conversion_c == 'c')
	{
		tmp = ft_strdup_c(va_arg(*arg_list, unsigned int));
		if (!tmp)
			return(NULL);
		return (tmp);
	}
	else if (conversion_c == 's')
	{
		tmp = ft_strdup(va_arg(*arg_list, char *));
		if (!tmp)
			tmp = ft_strdup("(null)");
		return (tmp);
	}
	return (NULL);
}

void	init_format_info(t_format_info **format_info)
{
	(**format_info).min_width = -1;
	(**format_info).minus = 0;
	(**format_info).precision= -1;
	(**format_info).value = NULL;
}

t_format_info	*ft_gen_format_info(char *target, va_list *arg_list)
{
	int		res;
	int		index;
	t_format_info	*format_info;

	format_info = malloc(sizeof(t_format_info) * 1);
	if (!format_info)
		return (NULL);
	init_format_info(&format_info);
	format_info->conversion_c = target[ft_strlen(target) - 1];
	index = 1;
	res = -1;
	while (!ft_isconversion_c(target[index]))
	{
		while (ft_isdigit(target[index]))
		{
			if (res == -1)
				res = 0;
			res = res * 10 + CTOI(target[index]);
			index++;
		}
		format_info->min_width = res;
		res = -1;
		if (target[index] == '-')
		{
			format_info->minus = 1;
			index++;
		}
		if (target[index] == '.')
		{
			res = 0;
			index++;
			while (ft_isdigit(target[index]))
			{
				res = res * 10 + CTOI(target[index]);
				index++;
			}
		}
		format_info->precision = res;
	}
	format_info->value = ft_get_value(format_info->conversion_c, arg_list);
	return (format_info);
}

char	*ft_apply_precision(char conversion_c, int precision, char *new_target)
{
	if (precision == -1)
		return (new_target);
	if ((conversion_c == 'd' || conversion_c == 'i' || conversion_c == 'x') && precision == 0 && new_target[0] == '0')
		return (ft_getfirstn(new_target, 0));
	if (conversion_c == 'd' || conversion_c == 'i')
	{
		if (new_target[0] == '-' && ft_strlen(new_target) <= precision)
		{
			new_target[0] = '0';
			new_target = ft_fill_output(new_target, '0', precision - ft_strlen(new_target) + 1);
			new_target[0] = '-';
		}
		else if (ft_strlen(new_target) < precision)
			new_target = ft_fill_output(new_target, '0', precision - ft_strlen(new_target));
		return (new_target);
	}
	if ((conversion_c == 'x' || conversion_c == 'X') && ft_strlen(new_target) < precision)
		return (ft_fill_output(new_target, '0', precision - ft_strlen(new_target)));
	if ((conversion_c == 'c' || conversion_c == 's') && ft_strlen(new_target) > precision)
		return (ft_getfirstn(new_target, precision));
	return (new_target);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	ft_format(t_format_info *format_info)
{
	int	len;
	char	*new_target;

	new_target = ft_strdup(format_info->value);
	new_target = ft_apply_precision(format_info->conversion_c, format_info->precision, new_target);
	if (format_info->min_width > ft_strlen(new_target))
		new_target = ft_fill_output(new_target, ' ', format_info->min_width - ft_strlen(new_target));
		// new_target = ft_fill_output(new_target, ' ', format_info->min_width - ft_strlen(new_target));
	len = ft_strlen(new_target);
	// write(1, new_target, len);
	ft_putstr(new_target);
	free(new_target);
	free(format_info->value);
	free(format_info);
	return (len);
}


void	ft_putchar_increment_both(const char **str, int *count)
{
	ft_putchar((char)**str);
	(*count)++;
	(*str)++;
}

int	ft_printf(const char *format, ...)
{
	int	count;
	char	*target;
	va_list	arg_list;

	va_start(arg_list, format);
	count = 0;
	while (format && *format)
	{
		if (*format != '%')
			ft_putchar_increment_both(&format, &count);
		else
		{
			target = ft_get_format((char *)format);
			if (ft_isvalid_format(target))
				count += ft_format(ft_gen_format_info(target, &arg_list));
			format += ft_strlen(target);
			free(target);
		}
	}
	va_end(arg_list);
	return (count);
}


int	main(void)
{
	int	ret;

	ret = ft_printf("%.2s\n", "abc");
	ret = printf("%.2s\n", "abc");
	// ret = ft_printf("%3.3d %3.3s %3.3x\n", 10, "ABC", 128);
	// printf("%d\n", ret);
}
