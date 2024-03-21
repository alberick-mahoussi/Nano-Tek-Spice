##
## EPITECH PROJECT, 2023
## B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
## File description:
## Makefile
##

CXX = g++

SRC 	= 	sources/Nanotekspice.cpp	\
			sources/CreateChipset.cpp	\
			ParsingAndError/ErrorHandling.cpp	\
			sources/Components/Input.cpp	\
			sources/Components/Output.cpp	\
			sources/Components/True.cpp	\
			sources/Components/False.cpp	\
			sources/Components/Clock.cpp	\
			sources/Components/LogicGates/AndElem.cpp	\
			sources/Components/LogicGates/OrElem.cpp	\
			sources/Components/LogicGates/NotElem.cpp	\
			sources/Components/LogicGates/XorElem.cpp	\
			sources/Components/Gates/4001Gate.cpp	\
			sources/Components/Gates/4011Gate.cpp	\
			sources/Components/Gates/4030Gate.cpp	\
			sources/Components/Gates/4069Gate.cpp	\
			sources/Components/Gates/4071Gate.cpp	\
			sources/Components/Gates/4081Gate.cpp	\

OBJ 	=		$(SRC:.cpp=.o)

NAME	= 		nanotekspice

CXXFLAGS = -W -Wextra -Werror -I./include -I./ParsingAndError -I./Components -std=c++17 -g3

all:	$(NAME)

$(NAME): 	$(OBJ)
		$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re