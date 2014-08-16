MUDUO_DIRECTORY ?= $(HOME)/build/release-install
#MUDUO_DIRECTORY ?= $(HOME)/build/install
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib
SRC = ./

CXXFLAGS = -g -O0 -Wall -Wextra -Werror \
	   -Wconversion -Wno-unused-parameter \
	   -Wold-style-cast -Woverloaded-virtual \
	   -Wpointer-arith -Wshadow -Wwrite-strings \
	   -march=native -rdynamic \
	   -I$(MUDUO_INCLUDE)

LDFLAGS = -L$(MUDUO_LIBRARY) -lmuduo_net -lmuduo_base -lpthread -lrt

all: chat_server chat_client
clean:
	rm -f  chat_client chat_server

chat_server: $(SRC)/saltadd.h chat_server.h chat_server.cc 
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
chat_client: $(SRC)/saltadd.h chat_client.cc 
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean
