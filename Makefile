CC=			gcc
NAME=		philo
RM=			rm -f
CD=			cd

CFLAGS=		\
			-Wall\
			-Werror\
			-Wextra\
			#-g -fsanitize=thread\

PTHREAD_FLAG= -lpthread

SRC_DIR=	source

SRCS=		$(shell find $(SRC_DIR) -maxdepth 1 -type f -name "*.c")

all: $(NAME)

$(NAME): $(SRCS)
		@$(CC) $(CFLAGS) $(SRCS) $(PTHREAD_FLAG) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all libft clean fclean re