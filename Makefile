NAME = philo
BONUS = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
SRC_DIR = ./src
SRC_BONUS_DIR = ./src_bonus
INC_DIR = ./src
OBJ_DIR = ./obj
OBJ_BONUS_DIR = ./obj_bonus
SRC_FILES = philo_main.c ps_atoi.c ph_utils.c routine.c death_checks.c\
			ph_utils_2.c ph_init_functions.c
SRC_BONUS_FILES = parser_philo_bonus.c\
			main_philo_bonus.c
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS_FILES = $(SRC_BONUS_FILES:%.c=$(OBJ_BONUS_DIR)/%.o)

all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/philo.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(BONUS): $(OBJ_BONUS_FILES)
	$(CC) $(CFLAGS) -o $(BONUS) $(OBJ_BONUS_FILES)

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c $(INC_DIR)/checker.h | $(OBJ_BONUS_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@	

FORCE:

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_BONUS_DIR):
	mkdir -p $(OBJ_BONUS_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

bonus_clean:
	rm -rf $(OBJ_BONUS_DIR)

bonus_fclean: bonus_clean
	rm -f $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus_clean bonus_fclean
