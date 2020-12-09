/*
Copyright (c) 2020, Patrik Nyström
All rights reserved.
This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
*/

#ifndef _TODOLIST_HPP
#define _TODOLIST_HPP
#include <string>
#include <vector>
#include "todo.hpp"

bool exists(std::string path);

// A TodoList class
class TodoList {
    private:
        std::vector<Todo> todos;
        std::string progDir;
        std::string saveFile;
    public:
        TodoList();
        void loadTodos();

        std::string validateCommand(std::string input);
        bool constructDate(std::string input, Todo& todo);
        bool constructTime(std::string input, Todo& todo);
        bool constructNote(std::string input, Todo& todo);

        std::string getInput();

        void addTodo();
        void listTodos();
        void delTodo();

        void run();
};

#endif