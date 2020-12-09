# Copyright (c) 2020, Patrik Nyström
# All rights reserved.
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

CXX := g++
CXXFLAGS := -O2 -std=c++11 -Wall -Wextra -pedantic
OBJS := obj/todolist.o obj/todo.o obj/main.o
PREFIX := /usr
BINDIR := ${PREFIX}/local/bin

.PHONY: all clean

all: main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o todolist $(OBJS)

obj/todolist.o: src/todolist.cpp
	$(CXX) $(CXXFLAGS) -c src/todolist.cpp -o obj/todolist.o

obj/todo.o: src/todo.cpp
	$(CXX) $(CXXFLAGS) -c src/todo.cpp -o obj/todo.o

obj/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

install:
	install -Dm755 todolist $(DESTDIR)$(BINDIR)/todolist

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/todolist

clean:
	rm -f todolist $(OBJS)