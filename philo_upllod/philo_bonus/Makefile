NAME = philo_bouns
SRCS = philo_bouns.c		utls_bouns.c  utls2_bouns.c  utls3_bouns.c

OBJ = $(SRCS:.c=.o)

CC = gcc  -g3 -pthread 

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CC)  $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re clean fclean all
