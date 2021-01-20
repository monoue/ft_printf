NAME = libft.a
CC = gcc
PART1 =
PART2 =
BONUS =
ADDED =
SRCS =		$(PART1) $(PART2) $(BONUS) $(ADDED) $(FT_PRINTF)
CFLAGS =	-Wall -Wextra -Werror
INCLUDE = libft.h


PART1 += ft_memset.c
PART1 += ft_bzero.c
PART1 += ft_memcpy.c
PART1 += ft_memccpy.c
PART1 += ft_memmove.c
PART1 += ft_memchr.c
PART1 += ft_memcmp.c
PART1 += ft_strlen.c
PART1 += ft_strlcpy.c
PART1 += ft_strlcat.c
PART1 += ft_strchr.c
PART1 += ft_strrchr.c
PART1 += ft_strnstr.c
PART1 += ft_strncmp.c
PART1 += ft_atoi.c
PART1 += ft_isalpha.c
PART1 += ft_isdigit.c
PART1 += ft_isalnum.c
PART1 += ft_isascii.c
PART1 += ft_isprint.c
PART1 += ft_toupper.c
PART1 += ft_tolower.c
PART1 += ft_calloc.c
PART1 += ft_strdup.c

PART2 += ft_substr.c
PART2 += ft_strjoin.c
PART2 += ft_strtrim.c
PART2 += ft_split.c
PART2 += ft_itoa.c
PART2 += ft_strmapi.c
PART2 += ft_putchar_fd.c
PART2 += ft_putstr_fd.c
PART2 += ft_putendl_fd.c
PART2 += ft_putnbr_fd.c

BONUS += ft_lstnew.c
BONUS += ft_lstadd_front.c
BONUS += ft_lstsize.c
BONUS += ft_lstlast.c
BONUS += ft_lstadd_back.c
BONUS += ft_lstdelone.c
BONUS += ft_lstclear.c
BONUS += ft_lstiter.c
BONUS += ft_lstmap.c

ADDED += ft_isspace.c
ADDED += ft_strnlen.c
ADDED += ft_strstr.c
ADDED += ft_putchar.c
ADDED += ft_putstr.c
ADDED += ft_putnbr.c
ADDED += ft_intlen.c
ADDED += ft_strjoin_free_both.c
ADDED += ft_strcmp.c
ADDED += ft_strdup_free.c
ADDED += ft_itoc.c
ADDED += ft_ctoa.c
ADDED += ft_xtoa.c
ADDED += ft_utoa.c
ADDED += ft_count_strs.c
ADDED += ft_str_is_numeric.c
ADDED += ft_strcpy.c
ADDED += get_next_line.c

OBJS =		$(SRCS:%.c=%.o)

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -I./$(INCLUDE) -o $@ -c $<

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
