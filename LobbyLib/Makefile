#!/bin/bash
DIR=.
INCLUDE=-I../LobbyServer
SRC=$(DIR)
CPP=g++
DEBUG=-g -Wall
BINDIR:=$(DIR)/../libs
TARGET:=lobbylib.so
#TARGET:=PlayerMgr.so
#CFLAGS:= -std=c++11 -lpthread -llua  -ldl  -fPIC -Wl,-E
CFLAGS:= -lpthread -llua  -ldl  -fPIC -Wl,-E
SHARED:= -shared
sources:=$(wildcard $(SRC)/*.cpp)
#objects:=$(subset $(SRC)/, $(BINDIR)/, $(sources))
objs:=$(sources:.cpp=.o)

$(TARGET): $(objs)
	@mkdir -p $(BINDIR)
	$(CPP) $(SHARED) $(DEBUG) $(INCLUDE) $(objs) -o $(BINDIR)/$(TARGET) $(CFLAGS) 
	@chmod 755 $(BINDIR)/$(TARGET)
$(objs): %.o: %.cpp
	$(CPP) $(DEBUG) $(INCLUDE) -c $< -o $@  $(CFLAGS)

.PHONY: clean run
clean:
	-rm -f $(BINDIR)/$(TARGET) $(objs)
run:
	cd $(BINDIR);./$(TARGET)
