/*
Copyright (c) 2020, Patrik Nyström
All rights reserved.
This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
*/

#ifndef _TODO_HPP
#define _TODO_HPP
#include <string>

// A Todo class
class Todo {
    private:
        std::string note;
        std::string date;
        std::string time;
    public:
        std::string getNote();
        std::string getDate();
        std::string getTime();

        void setNote(std::string _note);
        void setDate(std::string _date);
        void setTime(std::string _time);
};

#endif