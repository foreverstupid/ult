CC = g++
CXXFLAGS = -Wall -g -fno-exceptions
LDFLAGS = -lm
LIBS =

SRC_DIR = src
HEADER_DIR = src/headers
OBJ_DIR = obj

SRC_FILES = text_operations.cpp

SRCS = $(SRC_FILES:%.cpp=$(SRC_DIR)/%.cpp)
OBJS = $(SRC_FILES:%.cpp=$(OBJ_DIR)/%.o)
NAME = ult

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER_DIR)/%.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@

$(NAME): $(SRC_DIR)/main.cpp $(OBJS)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $^ $(LIBS) -o $@

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(SRCS)
	$(CC) -MM $^ | sed -e 's#[a-z_A-Z0-9]*\.o#$(OBJ_DIR)/&#' > $@

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f deps.mk
	rm -f $(NAME)
