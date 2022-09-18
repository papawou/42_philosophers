NAME := philo

CC := gcc
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS :=	-g -fdiagnostics-color=always
else
	CFLAGS :=	-Wall -Wextra -Werror
endif

INC_DIR := -I./includes
SRC_DIR := ./src
OBJ_DIR := ./obj

SRC := main.c time.c msg.c rick.c philosopher.c clean_exit.c parser/parser.c parser/parser_atoi.c
OBJ := ${addprefix $(OBJ_DIR)/, ${SRC:.c=.o}}

LIBS := 
LIBSINC := 

all : $(NAME)

$(NAME)	:	$(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(INC_DIR) $(LIBSINC) $(LIBS) -lpthread

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(INC_DIR) $(LIBSINC)

%.a :
	$(MAKE) -C $(@D)

clean :
	${RM} $(OBJ)

fclean : clean
	${RM} $(NAME)

re : fclean all

.PHONY : all clean fclean re