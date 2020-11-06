NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror


SRCS = parse.c printnum1.c printnum2.c printcsper.c high.c
OBJS = $(SRCS:.c=.o)

.PHONY: all, clean, fclean, re 
HEADERS = ft_printf.h


all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# $@ -Имя цели обрабатываемого правила
# $< Имя первой зависимости обрабатываемого правила
%.o: %.c $(HEADERS)
	@gcc $(FLAGS) -c $< -o $@
clean:
	rm -rf *.o

fclean: clean
	rm -rf *.a
	
re: fclean all

run: $(NAME)
	gcc main.c $(NAME)

