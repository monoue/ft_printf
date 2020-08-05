#include <stdarg.h>
#include <unistd.h>

#define MIN(x, y) x <= y ? x : y
#define MAX(x, y) x >= y ? x : y
#define CTOI(n) n - '0'

typedef struct	s_format_info
{
	int		min_width;
	int		precision;
	char	conv_c;
}				t_format_info;

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

void	init_format_info(t_format_info *format_info)
{
	format_info->min_width = 0;
	format_info->precision = -1;
	format_info->conv_c = '`\0';
}

void	parse_min_width(const char **format, t_format_info *format_info)
{
	while (ft_isdigit(**format))
	{
		format_info->min_width *= 10;
		format_info->min_width += CTOI(**format);
		(*format)++;
	}
}

void	parse_precision(const char **format, t_format_info *format_info)
{
	if (**format != '.')
		return ;
	(*format)++;
	format_info->precision = 0;
	while (ft_isdigit(**format))
	{
		format_info->precision *= 10;
		format_info->precision += CTOI(**format);
		(*format)++;
	}
}

void	parse_conversion_c(const char **format, t_format_info *format_info)
{
	format_info->conv_c = **format;
	if (**format)
		(*format)++;
}

int	display_s(char *str, t_format_info *format_info)
{
	int	count;
	int	len;

	count = 0;
	len	= ft_strlen(str);
	if (str == NULL)
		str = "(null)";
	if (format_info->precision != -1 && len > format_info->precision) //
		len = format_info->precision;
	while (format_info->min_width > len)
	{

	}
}

int	display_arg(t_format_info *format_info, va_list *args)
{
	if (format_info->conv_c == 's')
		return (display_s(va_arg(*args, char *), format_info));
		// ここで引数の２番目以降を取ってくる
	// if (format_info->conversion_c == 'd')
	// 	return (display_d(va_arg(*args, int), format_info));
	// if (format_info->conversion_c == 'x')
	// 	return (display_x(va_arg(*args, unsigned int), format_info));
	// return (0);
}

int	parse_info(const char **format, va_list *args)
{
	t_format_info	format_info;

	init_format_info(&format_info);
	(*format)++;
	parse_min_width(format, &format_info);
	parse_precision(format, &format_info);
	parse_conversion_c(format, &format_info);
	return (display_arg(&format_info, args));
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			// format の % のインクリメント等をしたいので、format はポインタで渡している
			int ret = parse_info(&format, &args);
		}
	}
}