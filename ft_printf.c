/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:57:30 by monoue            #+#    #+#             */
/*   Updated: 2020/08/06 08:44:58 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			init_format_info(t_format_info **info)
{
	(**info).min_width = -1;
	(**info).minus = 0;
	(**info).zero = 0;
	(**info).precision= -1;
	(**info).value = NULL;
	(**info).c_null = 0;
}

char			*ft_fill_output_space(char *str, int len, t_format_info *info)
{
	if (len < 0)
		return (str);
	if (info->minus)
		while (len--)
			str = ft_strjoin_free_both(str, ft_ctoa(' '));
	else if (info->zero && info->precision == -1 && str[0] && str[0] == '-')
	{
		str[0] = '0';
		while (len--)
			str = ft_strjoin_free_both(ft_ctoa('0'), str);
		str[0] = '-';
	}
	else if (info->precision != -1)
		while (len--)
			str = ft_strjoin_free_both(ft_ctoa(' '), str);
	else if (info->zero)
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

char			*ft_fill_output(char *str, char c, int len, t_format_info *info)
{
	if (len < 0)
		return (str);

	if (info->minus && info->precision != -1)
	{
		while (len)
		{
			str = ft_strjoin_free_both(ft_ctoa(c), str);
			len--;
		}
	}
	else if (info->minus)
	{
		while (len)
		{
			str = ft_strjoin_free_both(str, ft_ctoa(c));
			len--;
		}
	}
	while (len)
	{
		str = ft_strjoin_free_both(ft_ctoa(c), str);
		len--;
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

char			*return_ctoa_and_check_null_c(t_format_info *format_info,
va_list *arg_list)
{
	char			*tmp;
	unsigned int	c;

	c = va_arg(*arg_list, unsigned int);
	if (c == 0)
	{
		tmp = ft_ctoa('1');
		format_info->c_null = 1;
	}
	else
		tmp = ft_ctoa(c);
	return (tmp);
}

char			*ft_string_arg_to_a(va_list *arg_list)
{
	char	*tmp;

	tmp = ft_strdup(va_arg(*arg_list, char *));
	if (!tmp)
		tmp = ft_strdup("(null)");
	return (tmp);
}

void			*ft_get_value(t_format_info *info, va_list *arg_list)
{
	if (info->conv_c == 'd' || info->conv_c == 'i')
		return (ft_itoa((long)va_arg(*arg_list, int)));
	else if (info->conv_c == 'u')
		return (ft_utoa(va_arg(*arg_list, unsigned int)));
	else if (info->conv_c == 'x' || info->conv_c == 'X')
		return (ft_xtoa((size_t)va_arg(*arg_list, unsigned int), info));
	else if (info->conv_c == 'p')
		return (ft_xtoa((size_t)va_arg(*arg_list, void *), info));
	else if (info->conv_c == 'c')
		return (return_ctoa_and_check_null_c(info, arg_list));
	else if (info->conv_c == '%')
		return (ft_ctoa('%'));
	else if (info->conv_c == 's')
		return (ft_string_arg_to_a(arg_list));
	return (NULL);
}

int				minwidth_o_prec_to_int(char *target, int *index)
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

void			ft_set_index_when_invalid_prec(char *target, int *index)
{
	(*index)++;
	while (ft_isdigit(target[*index]))
		(*index)++;
}

void			set_minus_increment_index(int *index, t_format_info *info)
{
	info->minus = 1;
	(*index)++;
}

void			set_zero_minwidth_minus_prec(char *target, int *index,
t_format_info *info)
{
	if (target[*index] == '0')
		info->zero = 1;
	if (ft_isdigit(target[*index]))
		info->min_width = minwidth_o_prec_to_int(target, &(*index));
	if (target[*index] == '-')
		set_minus_increment_index(&(*index), info);
	if (target[*index] == '.')
	{
		(*index)++;
		if (target[*index] == '-')
			ft_set_index_when_invalid_prec(target, &(*index));
		else
			info->precision = minwidth_o_prec_to_int(target, &(*index));
	}
}

t_format_info	*ft_gen_format_info(char *target, va_list *arg_list)
{
	int				index;
	t_format_info	*info;

	info = malloc(sizeof(t_format_info) * 1);
	if (!info)
		return (NULL);
	init_format_info(&info);
	info->conv_c = target[ft_strlen(target) - 1];
	index = 1;
	while (!ft_isconversion_c(target[index]))
		set_zero_minwidth_minus_prec(target, &index, info);
	info->value = ft_get_value(info, arg_list);
	return (info);
}

char			*ft_apply_precision(char *new_target, t_format_info *info)
{
	if (info->precision == -1)
		return (new_target);
	if ((info->conv_c == 'd' || info->conv_c == 'i' || info->conv_c == 'u'
	||info->conv_c == 'x' || info->conv_c == 'X' || info->conv_c == 'p')
	&& info->precision == 0 && new_target[0] == '0')
		return (ft_free_and_return_null_c(new_target));
	if (info->conv_c == 'd' || info->conv_c == 'i' || info->conv_c == 'u'
	|| info->conv_c == 'p')
	{
		if (new_target[0] == '-' && ft_strlen(new_target) <= info->precision)
		{
			new_target[0] = '0';
			new_target = ft_fill_output_zero(new_target,
			info->precision - ft_strlen(new_target) + 1);
			new_target[0] = '-';
		}
		else if (ft_strlen(new_target) < info->precision)
			new_target = ft_fill_output_zero(new_target,
			info->precision - ft_strlen(new_target));
		return (new_target);
	}
	if ((info->conv_c == 'x' || info->conv_c == 'X')
	&& ft_strlen(new_target) < info->precision)
		return (ft_fill_output(new_target, '0',
		info->precision - ft_strlen(new_target), info));
	if ((info->conv_c == 'c' || info->conv_c == 's')
	&& ft_strlen(new_target) > info->precision)
		return (ft_cut_by_precision(new_target, info->precision));
	return (new_target);
}

int				ft_put_result(t_format_info *info)
{
	int		len;
	char	*new_target;

	new_target = ft_strdup(info->value);
	new_target = ft_apply_precision(new_target, info);
	if (info->conv_c == 'p')
		new_target = ft_strjoin_free_both(ft_strdup("0x"), new_target);
	if (info->min_width > ft_strlen(new_target))
		new_target = ft_fill_output_space(new_target,
		info->min_width - ft_strlen(new_target), info);
	len = ft_strlen(new_target);
	if (info->c_null == 1)
		ft_putstr_n(new_target, len);
	else
		ft_putstr(new_target);
	SAFE_FREE(new_target);
	SAFE_FREE(info->value);
	SAFE_FREE(info);
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
// 	// このケースでデバッグするところから！
// 	ft_printf("[%.7s]\n", "hello");
// }
