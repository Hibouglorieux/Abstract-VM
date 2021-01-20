NAME = avm

FILES = main.cpp OperandCreator.cpp AVMcontainer.cpp readAVM.cpp exceptions.cpp

INCLUDES = src/Operand.hpp src/Operand.tpp

SRC = $(addprefix src/, $(FILES))

OBJ =  $(addprefix obj/, $(FILES:.cpp=.o))

COMPILE_FLAGS = -Wall -Wextra -g -std=gnu++14



all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $^ -o $@

obj/%.o: src/%.cpp $(INCLUDES) src/*.hpp
	@mkdir -p obj
	$(CXX) $(COMPILE_FLAGS) -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all
