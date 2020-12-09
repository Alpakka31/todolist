/*
Copyright (c) 2020, Patrik Nyström
All rights reserved.
This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
*/

#include <string>
#include "todo.hpp"

// Getter for note
std::string Todo::getNote() {
    return this->note;
}

// Getter for date
std::string Todo::getDate() {
    return this->date;
}

// Getter for time
std::string Todo::getTime() {
    return this->time;
}

// Setter for note
void Todo::setNote(std::string _note) {
    this->note = _note;
}

// Setter for date
void Todo::setDate(std::string _date) {
     this->date = _date;
}

// Setter for time
void Todo::setTime(std::string _time) {
    this->time = _time;
}