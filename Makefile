NAME	= libftprintf.a
CC		= gcc
SRCS	=
OBJS	= $(SRCS:%.c=%.o)
CLIBS	= -L . -lft
CFLAGS	= -Wall -Wextra -Werror

SRCS += ft_printf.c
SRCS += ft_printf_utils.c
SRCS += ft_printf_utils2.c
SRCS += cut_out_format.c
SRCS += init_format_info.c
SRCS += is.c
SRCS += set_zero_minwidth_minus_prec.c
SRCS += put_result.c
SRCS += toa_malloc.c
SRCS += apply_margin.c
SRCS += fill_with_zero.c

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
