#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>


typedef struct s_printf
{
    int width;
    int prec;
    int flag;
    char *value;
    char *f;
    char spec;
    int len;
    va_list ap;
}              t_printf;



int ft_strlen(char *s)
{
    int i;

    i = 0;
    while(s[i])
        i++;
    return (i);
}

int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}


void * ft_memset(void *p, int c, int size)
{
    unsigned char *tmp;

    tmp = p;
    while (size--)
    {
        *tmp = (unsigned char)c;
        tmp++;
    }
    return(p);

}

int ft_atoi(char *s)
{
    int res;
    int i;

    i = 0;
    res = 0;
    while (ft_isdigit(s[i]))
    {
        res = res * 10 + s[i] - '0';
        i++;
    }
    return (res);
}

char *ft_strdup(char *s)
{
    char *res;
    int i;

    if (!s)
        return (NULL);
    i = 0;
    res = malloc(sizeof(char) * ft_strlen(s) + 1);
    if (!res)
        return (NULL);
    while(s[i])
    {
        res[i] = s[i];
        i++;
    }
    return (res);
}

char *ft_strjoin(char *s1, char *s2)
{
    char *res;
    int i;
    int j;

    i = j = 0;
    res = malloc(sizeof(char) * (ft_strlen(s1) +ft_strlen(s2) + 1));
    if (!res)
        return (NULL);
    while(s1[i])
    {
        res[i] = s1[i];
        i++;
    }
    while(s2[j])
    {
        res[i + j] = s2[j];
        j++;
    }
    return (res);
}

char *ft_strjoin_free(char *s1, char *s2)
{
    char *res;
    int i;
    int j;

    i = j = 0;
    res = malloc(sizeof(char) * (ft_strlen(s1) +ft_strlen(s2) + 1));
    if (!res)
        return (NULL);
    while(s1[i])
    {
        res[i] = s1[i];
        i++;
    }
    while(s2[j])
    {
        res[i + j] = s2[j];
        j++;
    }
    free(s1);
    free(s2);
    return (res);
}

char *ft_itoa_base(int n, int base)
{
    char *res;

    res = malloc(sizeof(char) * 2);
    if (!res)
        return (NULL);
    if (n == INT_MIN)
    {
        if (base == 10)
            return (ft_strdup("-2147483648"));
        else
            return (ft_strdup("80000000"));
    }
    else if (n < 0)
    {
        res[0] = '-';
        res[1] = 0;

    }
    else if (n == 0)
    {
        res[0] = '0';
        res[1] = 0;
    }
    else if (n < base)
    {
        res[0] = "0123456789abcdef"[n];
        res[1] = 0;
    }
    else
    {
        free(res);
        res = ft_strjoin(ft_itoa_base(n / base, base), ft_itoa_base(n % base, base));
    }
    return (res);
}



void ft_padding(t_printf *p, char c, int size)
{
    char *padding;

    padding = malloc(sizeof(char) * size + 1);
    if (!padding)
        return;
    ft_memset(padding, c, size);
    p->value = ft_strjoin(padding, p->value);
}


void apply_prec(t_printf *p)
{
    if (p->prec == -1)
        return ;
    if (p->len > p->prec && p->spec == 's')
        ft_memset(p->value + p->prec, 0, p->len - p->prec);
    else if (p->prec == 0 && p->value[0] == '0' && (p->spec == 'x' || p->spec == 'd'))
        ft_memset(p->value, 0, 1);
    else if (p->len < p->prec && (p->spec == 'x' || p->spec == 'd'))
        ft_padding(p, '0', p->prec - p->len);
}

void apply_width(t_printf *p)
{
    if (p->width == -1)
        return ;
    if (p->width > p->len)
        ft_padding(p, ' ', p->width - p->len);
}

void ft_format(t_printf *p)
{
    if (p->spec == 's')
        p->value = ft_strdup(va_arg(p->ap, char *));
    else if (p->spec == 'd')
        p->value = ft_itoa_base(va_arg(p->ap, int), 10);
    else if (p->spec == 'x')
        p->value = ft_itoa_base(va_arg(p->ap, int), 16);
    if (p->value == NULL && p->spec == 's')
        p->value = ft_strdup("(null)");
    p->len = ft_strlen(p->value);
    apply_prec(p);
    p->len = ft_strlen(p->value);
    apply_width(p);
    p->len = ft_strlen(p->value);
}

void ft_parse(t_printf *p)
{
    p->prec = -1;
    p->width = -1;
    if (*p->f >= '0' && *p->f <= '9')
    {
        p->width = ft_atoi(p->f);
        while (ft_isdigit(*p->f))
            p->f++;
    }
    if (*p->f == '.')
    {
        p->f++;
        if (*p->f >= '0' && *p->f <= '9')
        {
            p->prec = ft_atoi(p->f);
            while (ft_isdigit(*p->f))
            p->f++;
        }
        else
            p->prec = 0;
    }
    p->spec = *p->f;
    ft_format(p);
}



int ft_printf(char *format, ...)
{
    t_printf p;
    int ret;

    ret = 0;
    va_start(p.ap, format);
    p.f = format;
    while (*p.f)
    {
        if (*p.f == '%')
        {
            p.f++;
            ft_parse(&p);
            write(1, p.value, p.len);
            ret += p.len;
        }
        else
        {
            write(1, p.f, 1);
            ret++;
        }
        p.f++;
    }
    va_end(p.ap);
    return (ret);
}
