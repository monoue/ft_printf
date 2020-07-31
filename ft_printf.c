/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:57:30 by monoue            #+#    #+#             */
/*   Updated: 2020/07/31 20:50:45 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_format_info(t_format_info **format_info)
{
	(**format_info).min_width = -1;
	(**format_info).minus = 0;
	(**format_info).zero = 0;
	(**format_info).precision= -1;
	(**format_info).value = NULL;
}

char	*ft_fill_output_space(char *str, int len, t_format_info *format_info)
{
	if (len < 0)
		return (str);
	if (format_info->minus)
		while (len--)
			str = ft_strjoin_free_both(str, ft_ctoa(' '));
	else if (format_info->zero && format_info->precision == -1 && str[0] && str[0] == '-')
	{
		str[0] = '0';
		while (len--)
			str = ft_strjoin_free_both(ft_ctoa('0'), str);
		str[0] = '-';
	}
	else if (format_info->precision != -1)
		while (len--)
			str = ft_strjoin_free_both(ft_ctoa(' '), str);
	else if (format_info->zero)
		while (len--)
			str = ft_strjoin_free_both(ft_ctoa('0'), str);
	else
		while (len--)
			str = ft_strjoin_free_both(ft_ctoa(' '), str);
	return (str);
}

int	ft_isconversion_c(char c)
{
	// return (c == 'c' || c == 'd' || c == 'i' || c == 'x' || c == 'X' || c == 's' || c == 'u' || c == 'p');
	return (c == 'c' || c == 'd' || c == 'i' || c == 'x' || c == 'X' || c == 's' || c == 'u' || c == 'p' || c == '%');
}

int	ft_isflag(char c)
{
	return (c == '-' || c == '0' || c == '.' || c == '*');
}

char	*ft_free_and_return_null_c(char *str)
{
	char	*res;

	if (!str)
		return (NULL);
	res = ft_substr(str, 0, 0);
	free(str);
	return (res);
}

char	*ft_cut_by_precision(char *str, int len)
{
	char	*res;

	if (!str)
		return (NULL);
	res = ft_substr(str, 0, len);
	free(str);
	return (res);
}

char	*ft_fill_output(char *str, char c, int len, t_format_info *format_info)
{
	if (len < 0)
		return (str);
	if (format_info->minus)
	{
		if (format_info->precision != -1)
		{
			while (len--)
				str = ft_strjoin_free_both(ft_ctoa(c), str);
		}
		else
		{
			while (len--)
				str = ft_strjoin_free_both(str, ft_ctoa(c));
		}
	}
	else
	{
		while (len--)
			str = ft_strjoin_free_both(ft_ctoa(c), str);
	}
	return (str);
}

char	*ft_fill_output_zero(char *str, int len)
{
	if (len < 0)
		return (str);
	while (len--)
		str = ft_strjoin_free_both(ft_ctoa('0'), str);
	return (str);
}

// char	*ft_get_format(char *format)
// {
// 	int	index;

// 	index = 1;
// 	while (ft_isflag(format[index])|| ft_isdigit(format[index]))
// 		index++;
// 	if (ft_isconversion_c(format[index]))
// 		index++;
// 	return (ft_substr(format, 0, index));
// }

char	*ft_get_format(char *format, va_list *arg_list)
{
	int		fmt_i;
	char	*str;
	// char	*tmp;
	// int		str_i;
	// int		tmp_i;

	str = ft_strdup("%");
	// str[0] = '%';
	fmt_i = 1;
	// str_i = 1;
	while (ft_isflag(format[fmt_i]) || ft_isdigit(format[fmt_i]) || format[fmt_i] == '*')
	{
		if (format[fmt_i] == '*')
			str = ft_strjoin_free_both(str, va_arg(*arg_list, char *));
		// {
		// 	tmp = va_arg(*arg_list, char *);
		// 	while (*tmp)
		// 		str[str_i++] = *tmp++;
		// }
		else
			str = ft_strjoin_free_both(str, ft_ctoa(format[fmt_i]));
			// str[str_i++] = format[fmt_i];
		fmt_i++;
	}
	// return (ft_str)
	// // 	index++;
	if (ft_isconversion_c(format[fmt_i]))
		str = ft_strjoin_free_both(str, ft_ctoa(format[fmt_i]));
		// str[str_i] = format[fmt_i];
	// free 必要？？
	return (str);
	// return (ft_substr(format, 0, index));
}

int	ft_isvalid_format(char *target)
{
	if (!target || ft_strlen(target) < 2)
		return (0);
	return (ft_isconversion_c(target[ft_strlen(target) - 1]));
}

void		*ft_get_value(t_format_info *format_info, va_list *arg_list)
{
	char	*tmp;

	if (format_info->conversion_c == 'd' || format_info->conversion_c == 'i')
		return (ft_itoa((long)va_arg(*arg_list, int)));
	else if (format_info->conversion_c == 'u')
		return (ft_utoa(va_arg(*arg_list, unsigned int)));
	else if (format_info->conversion_c == 'x' || format_info->conversion_c == 'X')
		return (ft_xtoa((size_t)va_arg(*arg_list, unsigned int), format_info));
	else if (format_info->conversion_c == 'p')
		return (ft_xtoa((size_t)va_arg(*arg_list, void *), format_info));
	else if (format_info->conversion_c == 'c')
	{
		tmp = ft_ctoa(va_arg(*arg_list, unsigned int));
		if (!tmp)
			return(NULL);
		return (tmp);
	}
	else if (format_info->conversion_c == '%')
	{
		tmp = ft_ctoa('%');
		if (!tmp)
			return(NULL);
		return (tmp);
	}
	else if (format_info->conversion_c == 's')
	{
		tmp = ft_strdup(va_arg(*arg_list, char *));
		if (!tmp)
			tmp = ft_strdup("(null)");
		return (tmp);
	}
	return (NULL);
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
		if (target[index] == '0')
			format_info->zero = 1;
		while (ft_isdigit(target[index]))
		{
			if (res == -1)
				res = 0;
			res = res * 10 + CTOI(target[index]);
			index++;
		}
		format_info->min_width = res;
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
			format_info->precision = res;
		}
	}
	format_info->value = ft_get_value(format_info, arg_list);
	return (format_info);
}

char	*ft_apply_precision(char *new_target, t_format_info *format_info)
{
	if (format_info->precision == -1)
		return (new_target);
	if ((format_info->conversion_c == 'd' || format_info->conversion_c == 'i' || format_info->conversion_c == 'u' ||format_info->conversion_c == 'x' || format_info->conversion_c == 'X' || format_info->conversion_c == 'p') && format_info->precision == 0 && new_target[0] == '0')
		return (ft_free_and_return_null_c(new_target));
	if (format_info->conversion_c == 'd' || format_info->conversion_c == 'i' || format_info->conversion_c == 'u' || format_info->conversion_c == 'p')
	{
		if (new_target[0] == '-' && ft_strlen(new_target) <= format_info->precision)
		{
			new_target[0] = '0';
			new_target = ft_fill_output_zero(new_target, format_info->precision - ft_strlen(new_target) + 1);
			new_target[0] = '-';
		}
		else if (ft_strlen(new_target) < format_info->precision)
			new_target = ft_fill_output_zero(new_target, format_info->precision - ft_strlen(new_target));
		return (new_target);
	}
	if ((format_info->conversion_c == 'x' || format_info->conversion_c == 'X') && ft_strlen(new_target) < format_info->precision)
		return (ft_fill_output(new_target, '0', format_info->precision - ft_strlen(new_target), format_info));
	if ((format_info->conversion_c == 'c' || format_info->conversion_c == 's') && ft_strlen(new_target) > format_info->precision)
		return (ft_cut_by_precision(new_target, format_info->precision));
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
	int		len;
	char	*new_target;

	new_target = ft_strdup(format_info->value);
	new_target = ft_apply_precision(new_target, format_info);
	if (format_info->conversion_c == 'p')
		new_target = ft_strjoin_free_both(ft_strdup("0x"), new_target);
	if (format_info->min_width > ft_strlen(new_target))
		new_target = ft_fill_output_space(new_target, format_info->min_width - ft_strlen(new_target), format_info);
	len = ft_strlen(new_target);
	ft_putstr(new_target);
	new_target = NULL;
	free(new_target);
	format_info->value = NULL;
	free(format_info->value);
	format_info = NULL;
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
	int		count;
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
			// if (format[1] == '%')
			// {
			// 	ft_putchar_increment_both(&format, &count);
			// 	format += 2;

			// }
			// else
			// {
				// target = ft_get_format((char *)format);
				target = ft_get_format((char *)format, &arg_list);
				if (ft_isvalid_format(target))
					count += ft_format(ft_gen_format_info(target, &arg_list));
				format += ft_strlen(target);
				free(target);
			// }
		}
	}
	va_end(arg_list);
	return (count);
}


// int	main(void)
// {
// 	// int	ret;
// 	// int a = 5;

// 	printf("[%s]\n", "abc");
// 	ft_printf("[%s]\n", "abc");
// 	// printf("[%5p]\n", NULL);
// 	// ft_printf("[%5p]\n", NULL);
// }
