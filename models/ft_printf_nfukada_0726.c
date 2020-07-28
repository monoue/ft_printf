#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_info
{
	int		field;
	int		prec;
	int		minus;
	char	conv;
}				t_info;

int	is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

size_t	ft_strlen(char *str)
{
	size_t len = 0;
	while (str[len])
	{
		len++;
	}
	return (len);
}

char	*ft_strdup(char *s)
{
	size_t len = ft_strlen(s);
	char *str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	size_t i = 0;
	while (str[i])
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

void	init_info(t_info *info)
{
	info->field = 0;
	info->prec = -1;
	info->minus = 0;
	info->conv = '\0';
}

char *ft_itoa(int n, t_info *info)
{
	if (n == 0 && info->prec == 0)
		return (ft_strdup(""));
	int len = (n <= 0);
	int sign = (n >= 0 ? 1 : -1);
	int tmp = n;
	while (tmp)
	{
		len++;
		tmp /= 10;
	}
	if (info->prec >= len)
		len = info->prec + (n < 0);
	char *str = malloc(len + 1);
	if (str == NULL)
		return (str);
	str[len] = '\0';
	while (len--)
	{
		str[len] = n % 10 * sign + '0';
		n /= 10;
	}
	if (sign < 0)
		str[0] = '-';
	return (str);
}

char *ft_utoa(unsigned int n, t_info *info)
{
	char *base = "0123456789abcdef";
	int len = (n == 0);
	unsigned int tmp = n;

	if (info->prec == 0 && n == 0)
		return ft_strdup("");
	while (tmp)
	{
		len++;
		tmp /= 16;
	}
	if (info->prec > len)
		len = info->prec;
	char *str = malloc(len + 1);
	if (str == NULL)
		return (str);
	str[len] = '\0';
	while (len--)
	{
		str[len] = base[n % 16];
		n /= 16;
	}
	return (str);
}

int display_s(char *s, t_info *info)
{
	int count = 0;
	if (s == NULL)
		s = "(null)";
	int len = ft_strlen(s);
	if (info->prec != -1 && len > info->prec)
		len = info->prec;
	while (info->field > len)
	{
		write(1, " ", 1);
		info->field--;
		count++;
	}
	write(1, s, len);
	count += len;
	return (count);
}

int display_d(int n, t_info *info)
{
	int count = 0;
	char *str = ft_itoa(n, info);
	if (str == NULL)
		return (0);
	int len = ft_strlen(str);
	while (info->field > len)
	{
		write(1, " ", 1);
		info->field--;
		count++;
	}
	write(1, str, len);
	free(str);
	count += len;
	return (count);
}

int display_x(unsigned int x, t_info *info)
{
	int count = 0;
	char *str = ft_utoa(x, info);
	if (str == NULL)
	{
		return (0);
	}
	int len = ft_strlen(str);
	while (info->field > len)
	{
		write(1, " ", 1);
		info->field--;
		count++;
	}
	write(1, str, len);
	free(str);
	count += len;
	return (count);
}

int display_arg(t_info *info, va_list *ap)
{
	if (info->conv == 's')
		return (display_s(va_arg(*ap, char *), info));
	if (info->conv == 'd')
		return (display_d(va_arg(*ap, int), info));
	if (info->conv == 'x')
		return (display_x(va_arg(*ap, unsigned int), info));
	return (0);
}

int parse_field(const char **str, t_info *info)
{
	while (is_digit(**str))
	{
		info->field *= 10;
		info->field += **str - '0';
		(*str)++;
	}
	return (1);
}

int	parse_prec(const char **str, t_info *info)
{
	if (**str != '.')
	{
		return (1);
	}
	(*str)++;
	info->prec = 0;
	while (is_digit(**str))
	{
		info->prec *= 10;
		info->prec += **str - '0';
		(*str)++;
	}
	return (1);
}

int parse_conv(const char **str, t_info *info)
{
	info->conv = **str;
	if (**str)
	{
		(*str)++;
	}
	return (1);
}

int	parse_info(const char **str, va_list *ap)
{
	t_info info;

	init_info(&info);
	(*str)++;
	parse_field(str, &info);
	parse_prec(str, &info);
	parse_conv(str, &info);
	return (display_arg(&info, ap));
}

int	ft_printf(const char *str, ... )
{
	int count = 0;
	va_list ap;

	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			int ret = parse_info(&str, &ap);
			if (ret < 0)
			{
				count = -1;
				break ;
			}
			count += ret;
		}
		else
		{
			write(1, str, 1);
			count++;
			str++;
		}
	}
	va_end(ap);
	return (count);
}
