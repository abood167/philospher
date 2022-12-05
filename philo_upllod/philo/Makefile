NAME = philo
SRCS = philo.c		utls.c  utls2.c  utls3.c  utls4.c

OBJ = $(SRCS:.c=.o)

CC = gcc  -pthread

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC)  $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re clean fclean all
