OBJS = cwebserver.cpp

CC = g++

LINKER_FLAGS = -lpthread

OBJ_NAME = cwebserver

all : $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

