OBJS = cwebserver.cpp

CC = g++

LINKER_FLAGS = -lpthread

COMPILER_FLAGS = -std=c++11

OBJ_NAME = cwebserver

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

