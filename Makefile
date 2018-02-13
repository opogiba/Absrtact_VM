NAME    = absttact

CC      = clang++ -std=c++11


SRCS    =   main.cpp Operand.cpp Exceptions.cpp OperandFactory.cpp Token.cpp Lexer.cpp Parser.cpp AbstractVM.cpp

OBJS    = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(SRCS) -o $(NAME)
	@printf "[CC] %s\n" $(NAME)

.cpp.o:
	@printf "[CC] %s\n" $<
	@$(CC) $(CFLAGS) -c $<  -o $@

clean:
	@printf "[RM] objects\n"
	@rm -rf $(OBJS)

fclean: clean
	@printf "[RM] %s\n" $(NAME)
	@rm -rf $(NAME)

re: fclean all
