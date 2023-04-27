NAME		= springs

SRC_DIR		= src
INC_DIR		= include
SRC			= $(wildcard $(SRC_DIR)/*.cpp)
OBJ			= $(SRC:.cpp=.o)
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -I$(INC_DIR)
RM			= rm -rf

ifeq ($(OS), Windows_NT)
	CXXFLAGS += -lWs2_32
endif

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