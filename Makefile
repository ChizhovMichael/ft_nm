NAME	= 	ft_nm

LIBFT	=	./libft

HEADER	= 	./inc

SRCS	=	./ft_nm.c \
			./src/flags.c \
			./src/validate.c \
			./src/utils.c \
			./src/handler_elf32.c \
			./src/handler_elf64.c


OBJS	= 	$(SRCS:.c=.o)

#CFLAGS	=	-I

CFLAGS	=	-Wall -Wextra -Werror -I

.c.o:
		gcc $(CFLAGS) $(HEADER) -c $< -o $(<:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS)
		$(MAKE) bonus -C $(LIBFT)
		gcc $(OBJS) $(LIBFT)/libft.a -o $(NAME)

build:
		docker build -t name .
		docker run -it -v ${PWD}:/home name

clean:
		$(MAKE) clean -C $(LIBFT)
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)
		$(MAKE) fclean -C $(LIBFT)

re:		fclean all
		$(MAKE) re -C $(LIBFT)

.PHONY:		all clean fclean re
