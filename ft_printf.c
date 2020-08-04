/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:57:30 by monoue            #+#    #+#             */
/*   Updated: 2020/08/04 15:59:31 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


void			init_format_info(t_format_info **format_info)
{
	(**format_info).min_width = -1;
	(**format_info).minus = 0;
	(**format_info).zero = 0;
	(**format_info).precision= -1;
	(**format_info).value = NULL;
	(**format_info).c_null = 0;
}

char			*ft_fill_output_space(char *str, int len, t_format_info *format_info)
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

char			*ft_free_and_return_null_c(char *str)
{
	char	*res;

	if (!str)
		return (NULL);
	res = ft_substr(str, 0, 0);
	SAFE_FREE(str);
	return (res);
}

char			*ft_cut_by_precision(char *str, int len)
{
	char	*res;

	if (!str)
		return (NULL);
	res = ft_substr(str, 0, len);
	SAFE_FREE(str);
	return (res);
}

char			*ft_fill_output(char *str, char c, int len, t_format_info *format_info)
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

char			*ft_fill_output_zero(char *str, int len)
{
	if (len < 0)
		return (str);
	while (len--)
		str = ft_strjoin_free_both(ft_ctoa('0'), str);
	return (str);
}

char			*ft_get_format(const char **format, va_list *arg_list)
{
	char	*str;

	str = ft_strdup("%");
	(*format)++;
	while (ft_isflag(**format) || ft_isdigit(**format) || **format == '*')
	{
		if (**format == '*')
			str = ft_strjoin_free_both(str, ft_itoa(va_arg(*arg_list, int)));
		else
			str = ft_strjoin_free_both(str, ft_ctoa(**format));
		(*format)++;
	}
	if (ft_isconversion_c(**format))
	{
		str = ft_strjoin_free_both(str, ft_ctoa(**format));
		(*format)++;
	}
	return (str);
}

int				ft_isvalid_format(char *target)
{
	if (!target || ft_strlen(target) < 2)
		return (0);
	return (ft_isconversion_c(target[ft_strlen(target) - 1]));
}

void			*ft_get_value(t_format_info *format_info, va_list *arg_list)
{
	char	*tmp;
	unsigned int	c;

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
		c = va_arg(*arg_list, unsigned int);
		if (c == 0)
		{
			tmp = ft_ctoa('1');
			format_info->c_null = 1;
		}
		else
			tmp = ft_ctoa(c);
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

int				ft_get_min_width_o_prec(char *target, int *index)
{
	int	res;

	res = 0;
	while (ft_isdigit(target[*index]))
	{
		res = res * 10 + CTOI(target[*index]);
		(*index)++;
	}
	return (res);
}

t_format_info	*ft_gen_format_info(char *target, va_list *arg_list)
{
	int				res;
	int				index;
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
		if (ft_isdigit(target[index]))
			res = ft_get_min_width_o_prec(target, &index);


		// while (ft_isdigit(target[index]))
		// {
		// 	if (res == -1)
		// 		res = 0;
		// 	res = res * 10 + CTOI(target[index]);
		// 	index++;
		// }
		format_info->min_width = res;
		if (target[index] == '-')
		{
			format_info->minus = 1;
			index++;
		}
		if (target[index] == '.')
		{
			index++;
			if (target[index] == '-')
			{
				index++;
				while (ft_isdigit(target[index]))
					index++;
			}
			else
			{
				res = ft_get_min_width_o_prec(target, &index);
				// res = 0;
				// while (ft_isdigit(target[index]))
				// {
				// 	res = res * 10 + CTOI(target[index]);
				// 	index++;
				// }
				format_info->precision = res;
			}
		}
	}
	format_info->value = ft_get_value(format_info, arg_list);
	return (format_info);
}

char			*ft_apply_precision(char *new_target, t_format_info *format_info)
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

int				ft_put_result(t_format_info *format_info)
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
	if (format_info->c_null == 1)
		ft_putstr_n(new_target, len);
	else
		ft_putstr(new_target);
	SAFE_FREE(new_target);
	SAFE_FREE(format_info->value);
	SAFE_FREE(format_info);
	return (len);
}

int				ft_printf(const char *format, ...)
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
			target = ft_get_format(&format, &arg_list);
			if (ft_isvalid_format(target))
				count += ft_put_result(ft_gen_format_info(target, &arg_list));
			free(target);
		}
	}
	va_end(arg_list);
	return (count);
}

// int	main(void)
// {
// 	int	ret;
// 	// int a = 5;
	// printf("[%*c]\n", 5, 'a');
	// ft_printf("[%*s]\n", 32, "abc");
	// ft_printf("[%-5d]", 258);
	// printf("[%.*s]\n", -1, "hello");
	// printf("[%-.1s]\n", "hello");
	// printf("[%.*s]\n", -3, "hello");
	// ft_printf("[%.*s]\n", -3, "hello");
	// printf("[%.-3s]\n", "hello");
	// ft_printf("[%.-3s]\n", "hello");

// 	ret = ft_printf("%c\n", 0);
// 	printf("%d\n", ret);
// 	// ft_printf("%c", '\0');
// 	// printf("[%5p]\n", NULL);
// 	// ft_printf("[%5p]\n", NULL);
// }
