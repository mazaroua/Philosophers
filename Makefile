NAME=philo
CC=cc
FLAGS= -Wall -Werror -Wextra
SRC= main.c parsing.c utils.c
OBJ= $(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -pthread

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf *.o

fclean:clean
	rm -rf $(NAME)

re:fclean all

.PHONY: all fclean clean