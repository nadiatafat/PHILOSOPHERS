CC			= cc

NAME		= philo

CFLAG		= -Wall -Werror -Wextra -g3
PTHREADFLAG = -pthread

SRC_DIR		= ./srcs
SRC			= ${addprefix $(SRC_DIR)/,parsing.c init.c monitor_routine.c philo_action.c philo_routine.c end_process.c utils.c main.c}

OBJ			= $(SRC:.c=.o)

HEADER_DIR	= ./includes
HEADER		= ${HEADER_DIR}/philo.h


all: $(NAME)

$(NAME): $(OBJ) ${HEADER}
	@$(CC) $(CFLAG) -o $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	@$(CC) $(FLAG) $(PTHREADFLAG) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf fsanitize

fsanitize: 
	@$(CC) -fsanitize=thread $(CFLAG) -o fsanitize $(OBJ)

re: fclean all

.PHONY: all clean fclean re