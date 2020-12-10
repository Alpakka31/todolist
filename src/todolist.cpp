/*
Copyright (c) 2020, Patrik Nyström
All rights reserved.
This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
*/

#include <iostream>
#include <string>
#include <vector>
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>
#include <fstream>
#include <sstream>

#include "todo.hpp"
#include "todolist.hpp"

// Check if a file or a directory path exists
bool exists(std::string path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

TodoList::TodoList() {
    TodoList::loadTodos();
}

// Function that loads todos from the savefile
// back to the program
void TodoList::loadTodos() {
    // Get user home directory
    struct passwd* pw = getpwuid(getuid());
    char* homedir = pw->pw_dir;
    std::string temp(homedir, strlen(homedir));


    // Define program's paths
    progDir = temp + "/.todolist";
    saveFile = progDir + "/todos";

    // Check if paths exist
    if (exists(progDir) == false) {
        int okDir = mkdir(progDir.c_str(), 0755);
        if (!okDir) {
            ;;
        } else {
            std::cout << "Couldn't create a save directory for todos\n";
            exit(1);
        }
    }

    if (exists(saveFile) == false) {
        std::ofstream out(saveFile);
        if (out.is_open()) {
            ;;
        } else {
            std::cout << "Couldn't create a save file for todos\n";
            exit(1);
        }
        out.close();
    }


    // Load todos from the savefile back to the program
    std::ifstream file(saveFile);

    if (file.is_open()) {
        std::string line;

        while(std::getline(file, line)) {

            // Split the todo from the file by whitespace
            // and put it to a vector
            std::string buffer;
            std::stringstream ss(line);

            std::vector<std::string> tokens;

            while (ss >> buffer) {
                tokens.push_back(buffer);
            }

            // Create a 'new' todo
            // and put it back to the list of todos
            Todo todo = Todo();
            todo.setDate(tokens.at(0));
            todo.setTime(tokens.at(1));

            // If the todo's note has multiple words separated by space
            // then include them aswell
            std::string note;
            // Index 2 == the start of note in the todo
            for (size_t i = 2; i < tokens.size(); ++i) {
                note += tokens.at(i) + " ";
            }

            // Remove whitespace from the end
            note.erase(note.find_last_not_of(" ") + 1);
            todo.setNote(note);


            this->todos.push_back(todo);
        }
    } else {
        std::cout << "Couldn't open savefile!\n";
        exit(1);
    }
}

// Function that validates the command given in the program
std::string TodoList::validateCommand(std::string input) {
    if (input.length() == 0) {
        return "";
    }

    if (input.substr(0, 3) == "add") {
        return "add";
    } else if (input.substr(0, 4) == "list") {
        return "list";
    } else if (input.substr(0, 3) == "del") {
        return "del";
    } else if (input.substr(0, 4) == "exit") {
        return "exit";
    } else {
        return "";
    }
}

// Function that constructs, validates and sets the date the user gave
bool TodoList::constructDate(std::string input, Todo& todo) {
    if (input.length() == 0) {
        std::cout << "Empty date given\n";
        return false;
    }

    if (input.length() == 8) {
        // Check for non numerical characters
        for (size_t i = 0; i < input.length(); i++) {
            if (isdigit(input[i]) == false) {
                std::cout << "Date contains other characters than numbers\n";
                return false;
            }
        }

        // Define the last days of every months
        int lastDayOfMonth[12] = {
            31, 28, 31, 30,
            31, 30, 31, 31,
            30, 31, 30, 31,
        };

        // Check for Leap Year.
        // Checks the right day of February.
        if (std::stoi(input.substr(4)) % 4 == 0) {
            if (std::stoi(input.substr(4)) % 100 == 0) {
                if (std::stoi(input.substr(4)) % 400 == 0) {
                    lastDayOfMonth[1] = 29;
                } else {
                    lastDayOfMonth[1] = 28;
                }
            } else {
                lastDayOfMonth[1] = 29;
            }
        } else {
            lastDayOfMonth[1] = 28;
        }

        // Validate month
        if (std::stoi(input.substr(2, 2)) > 12 || std::stoi(input.substr(2, 2)) <= 0) {
            std::cout << "Invalid month\n";
            return false;
        }

        // Validate day
        if (std::stoi(input.substr(2, 2)) == 01) { // January
            if (std::stoi(input.substr(0, 2)) > lastDayOfMonth[0] || std::stoi(input.substr(0, 2)) <= 0) {
                std::cout << "Invalid day\n";
                return false;
            }
        } else if (std::stoi(input.substr(2, 2)) == 02) { // February
            if (std::stoi(input.substr(0, 2)) > lastDayOfMonth[1] || std::stoi(input.substr(0, 2)) <= 0) {
                std::cout << "Invalid day\n";
                return false;
            }
        } else if (std::stoi(input.substr(2, 2)) == 03) { // March
            if (std::stoi(input.substr(0, 2)) > lastDayOfMonth[2] || std::stoi(input.substr(0, 2)) <= 0) {
                std::cout << "Invalid day\n";
                return false;
            }
        } else if (std::stoi(input.substr(2, 2)) == 04) { // April
            if (std::stoi(input.substr(0, 2)) > lastDayOfMonth[3] || std::stoi(input.substr(0, 2)) <= 0) {
                std::cout << "Invalid day\n";
                return false;
            }
        } else if (std::stoi(input.substr(2, 2)) == 05) { // May
            if (std::stoi(input.substr(0, 2)) > lastDayOfMonth[4] || std::stoi(input.substr(0, 2)) <= 0) {
                std::cout << "Invalid day\n";
                return false;
            }
        } else if (std::stoi(input.substr(2, 2)) == 06) { // June
            if (std::stoi(input.substr(0, 2)) > lastDayOfMonth[5] || std::stoi(input.substr(0, 2)) <= 0) {
                std::cout << "Invalid day\n";
                return false;
            }
        } else if (std::stoi(input.substr(2, 2)) == 07) { // July
            if (std::stoi(input.substr(0, 2)) > lastDayOfMonth[6] || std::stoi(input.substr(0, 2)) <= 0) {
                std::cout << "Invalid day\n";
                return false;
            }
        } else if (input.substr(2, 2) == "08") { // August
            if (std::stoi(input.substr(0, 2)) > lastDayOfMonth[7] || std::stoi(input.substr(0, 2)) <= 0) {
                std::cout << "Invalid day\n";
                return false;
            }
        } else if (input.substr(2, 2) == "09") { // September
            if (std::stoi(input.substr(0, 2)) > lastDayOfMonth[8] || std::stoi(input.substr(0, 2)) <= 0) {
                std::cout << "Invalid day\n";
                return false;
            }
        } else if (std::stoi(input.substr(2, 2)) == 10) { // October
            if (std::stoi(input.substr(0, 2)) > lastDayOfMonth[9] || std::stoi(input.substr(0, 2)) <= 0) {
                std::cout << "Invalid day\n";
                return false;
            }
        } else if (std::stoi(input.substr(2, 2)) == 11) { // November
            if (std::stoi(input.substr(0, 2)) > lastDayOfMonth[10] || std::stoi(input.substr(0, 2)) <= 0) {
                std::cout << "Invalid day\n";
                return false;
            }
        } else if (std::stoi(input.substr(2, 2)) == 12) { // December
            if (std::stoi(input.substr(0, 2)) > lastDayOfMonth[11] || std::stoi(input.substr(0, 2)) <= 0) {
                std::cout << "Invalid day\n";
                return false;
            }
        }

        // Format: DD MM YYYY
        std::string d = input.substr(0, 2);
        std::string m = input.substr(2, 2);
        std::string y = input.substr(4);

        todo.setDate(d + "." + m + "." + y);
    } else {
        std::cout << "Date not long enough or too long\n";
        return false;
    }
    return true;
}


// Function that constructs, validates and sets the time the user gave
bool TodoList::constructTime(std::string input, Todo& todo) {
    if (input.length() == 0) {
        std::cout << "Empty time given\n";
        return false;
    }

    if (input.length() == 4) {
        // Check for non numerical characters
        for (size_t i = 0; i < input.length(); i++) {
            if (isdigit(input[i]) == false) {
                std::cout << "Time contains other characters than numbers\n";
                return false;
            }
        }
        // Format: HH MM
        if (std::stoi(input.substr(0, 2)) > 24 || std::stoi(input.substr(0, 2)) < 0) {
            std::cout << "Invalid time\n";
            return false;
        }
        if (std::stoi(input.substr(2)) > 59 || std::stoi(input.substr(2)) < 0) {
            std::cout << "Invalid time\n";
            return false;
        }
        std::string h = input.substr(0, 2);
        std::string m = input.substr(2);

        todo.setTime(h + ":" + m);
    } else {
        std::cout << "Time not long enough or too long\n";
        return false;
    }
    return true;
}

// Function that constructs and sets the note the user gave
bool TodoList::constructNote(std::string input, Todo& todo) {
    if (input.length() == 0) {
        std::cout << "Empty note given\n";
        return false;
    }

    // Maybe add a size limit????
    todo.setNote(input);
    return true;
}

// Get input from the user and return it
std::string TodoList::getInput() {
    std::string input;
    std::getline(std::cin, input);

    return input;
}

// Add a new todo to the todolist
void TodoList::addTodo() {
    Todo todo = Todo();
    std::cout << "Adding a new todo.\n\n";

    // NOTE
    std::cout << "Note: ";
    std::string note = TodoList::getInput();

    bool okNote = TodoList::constructNote(note, todo);
    if (okNote == false) {
        std::cout << "Failed to add a new todo\n";
        return;
    }

    // DATE
    std::cout << "Date (DDMMYYYY): ";
    std::string date = TodoList::getInput();

    bool okDate = TodoList::constructDate(date, todo);
    if (okDate == false) {
        std::cout << "Failed to add a new todo\n";
        return;
    }


    // TIME
    std::cout << "Time (HHMM): ";
    std::string time = TodoList::getInput();

    bool okTime = TodoList::constructTime(time, todo);
    if (okTime == false) {
        std::cout << "Failed to add a new todo\n";
        return;
    }

    this->todos.push_back(todo);

    // Add the todo to the savefile for loading purposes
    std::ofstream file;
    file.open(saveFile, std::ios_base::app);

    if (file.is_open()) {
        file << todo.getDate() + " " + todo.getTime() + " " + todo.getNote() + "\n";
    } else {
        std::cout << "Failed to add note to save file\n";
        exit(1);
    }
    file.close();

    std::cout << "Added a new todo to the todolist\n";
}

// Function that lists all of the todos to the terminal screen
void TodoList::listTodos() {
    if (this->todos.size() == 0) {
        std::cout << "No todos found!\n";
        return;
    }

    std::cout << "List of todos\n";

    int counter = 0; // The number of the todo
    for (auto td : this->todos) {
        std::string todo = std::to_string(counter) + ":  " + td.getDate() + "  " + td.getTime() + "\t" + td.getNote();
        std::cout << todo << "\n";
        counter++;
    }
}

// Function that deletes the todo from the list of todos
void TodoList::delTodo() {
    if (this->todos.size() == 0) {
        std::cout << "No todos found!\n";
        return;
    }

    std::cout << "Deleting a todo\n";

    // Get the number of todos in the todolist.
    int numberOfTodos = this->todos.size() - 1;

    if (numberOfTodos == 0) {
        std::cout << "Todo number " << "(0): ";
    } else {
        std::cout << "Todo number " << "(0-" << std::to_string(numberOfTodos) << "): ";
    }
    std::string todo = TodoList::getInput();

    if (todo.length() == 0) {
        std::cout << "No todo number given\n";
        return;
    }

    for (size_t i = 0; i < todo.length(); i++) {
        // Check for non numerical characters
        if (isdigit(todo[i]) == false) {
            std::cout << "Not a number!\n";
            return;
        }
    }

    if (std::stoi(todo) > numberOfTodos) {
        std::cout << "Todo with number of " << todo << " couldn't be found!\n";
        return;
    }

    // Create a todo for getting the information of the to be deleted todo
    Todo todoToDelete = this->todos.at(std::stoi(todo));

    std::string todoLine = todoToDelete.getDate() + " " + todoToDelete.getTime() + " " + todoToDelete.getNote();

    std::string line;
    std::ifstream rFile;
    std::string tempFilename = progDir + "/.tmp.todolist";


    // Read the current savefile
    rFile.open(saveFile);
    if (rFile.is_open()) {
        // Create a tempfile
        std::ofstream temp;
        temp.open(tempFilename);

        if (temp.is_open()) {
            while (std::getline(rFile, line)) {
                // Add every todo line to the tempfile
                // except the one that will be deleted
                if (line != todoLine) {
                    temp << line << std::endl;
                }
            }
        } else {
            std::cout << "Couldn't create temp file\n";
            exit(1);
        }
        temp.close();
    } else {
        std::cout << "Couldn't read save file\n";
        exit(1);
    }
    rFile.close();


    // Remove the old savefile and check for errors
    int checkRM = std::remove(saveFile.c_str());
    if (checkRM != 0) {
        std::cout << "Failed to remove old savefile\n";
        exit(1);
    }

    // Rename the tempfile to be the new savefile and check for errors
    int checkRN = std::rename(tempFilename.c_str(), saveFile.c_str());
    if (checkRN != 0) {
         std::cout << "Failed to rename temp file\n";
         exit(1);
    }
    this->todos.erase(this->todos.begin() + std::stoi(todo));

    std::cout << "Deleted a todo\n";
}

// Function that runs the todolist
void TodoList::run() {
    while (true) {
        std::cout << "commands: (add, del, list, exit)\n";
        std::cout << "> ";

        std::string cmd = TodoList::getInput();
        std::string validated = TodoList::validateCommand(cmd);

        if (validated == "") {
            std::cout << "Wrong command!\n";
            continue;
        } else if (validated == "add") {
            TodoList::addTodo();
            std::cout << "\n";
        } else if (validated == "del") {
            TodoList::delTodo();
            std::cout << "\n";
        } else if (validated == "list") {
            TodoList::listTodos();
            std::cout << "\n";
        } else if (validated == "exit") {
            break;
        }
    }
}