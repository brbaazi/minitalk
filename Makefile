NAME_1 = client
NAME_2 = server

NAME_1_BONUS = client_bonus
NAME_2_BONUS = server_bonus

SRC_CLIENT = client.c
SRC_SERVER = server.c

SRC_CLIENT_BONUS = client_bonus.c
SRC_SERVER_BONUS = server_bonus.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)
OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME_1) $(NAME_2)

$(NAME_1): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_1) $(OBJ_CLIENT)

$(NAME_2): $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_2) $(OBJ_SERVER)

bonus: $(NAME_1_BONUS) $(NAME_2_BONUS)

$(NAME_1_BONUS): $(OBJ_CLIENT_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_1_BONUS) $(OBJ_CLIENT_BONUS)

$(NAME_2_BONUS): $(OBJ_SERVER_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_2_BONUS) $(OBJ_SERVER_BONUS)

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_CLIENT_BONUS) $(OBJ_SERVER_BONUS)

fclean: clean
	rm -f $(NAME_1) $(NAME_2) $(NAME_1_BONUS) $(NAME_2_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
