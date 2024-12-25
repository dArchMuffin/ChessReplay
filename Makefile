GCC=gcc
RM=rm -f
SRC=src/*.c
INC=include/
OBJS=$(SCR:.c=.o)
NAME=chess
FLAGS=-I $(INC)
EXEC=./$(NAME)
VAL=valgrind --leak-check=full --track-origins=yes ./chess | grep "^=="

$(NAME): $(OBJS)
	$(GCC) $(SRC) $(FLAGS) -g -o $(NAME)
	$(EXEC)
	#$(VAL)

all: $(NAME) 

val:
	$(VAL)

run: 
	$(EXEC)

clean:
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re run
