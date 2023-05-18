NAME		= billiards

SRC_DIR		= src
INC_DIR		= include
SRC			= $(wildcard $(SRC_DIR)/*.cpp)
OBJ			= $(SRC:.cpp=.o)
CXX			= clang++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++2a -I$(INC_DIR)
RM			= rm -rf

all: $(NAME)

.cpp.o:
	@$(CXX) $(CXXFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJ)
	@$(CXX) $(OBJ) $(CXXFLAGS) -o $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all