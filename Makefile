LIB_OBJS = CWebServer.cpp utils.cpp Request.cpp Response.cpp

CC = g++

LINKER_FLAGS = -lpthread

COMPILER_FLAGS = -std=c++17

OBJ_NAME = cwebserver

all : $(LIB_OBJS)
	@mkdir -p lib
	$(CC) -fPIC $(LIB_OBJS) -shared -o lib/lib$(OBJ_NAME).so $(COMPILER_FLAGS) $(LINKER_FLAGS) 

demo :
	@mkdir -p bin
	$(CC) demo.cpp -Llib -l$(OBJ_NAME) -o bin/demo $(COMPILER_FLAGS) $(LINKER_FLAGS)
