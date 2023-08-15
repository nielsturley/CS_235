#include <iostream>
#include <fstream>
#include <sstream>
#include "LinkedList.h"

//I hated this lab SO FREAKING MUCH so I hope you enjoy all of my hate comments

int main(int argc, char* argv[]) {
    //input and output files from command prompt
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);

    //so it begins...
    LinkedList<std::string> list;

    for (std::string line; getline(in, line);) {
        std::string command, itemsToImport;
        if (line.size() == 0) continue;
        std::istringstream iss(line);
        iss >> command; //totally just stole this^^^ stuff from the help and hints section. Basic file input using getline
        out << command;

        //doing whatever function based on the input ("command") given.
        if (command == "Insert") {
            while (iss >> itemsToImport) {
                out << " " << itemsToImport;
                list.push_front(itemsToImport);
            }
        }
        if (command == "Clear") {
            list.clear();
            out << " OK";
        }
        if (command == "Empty") {
            if (list.empty()) {
                out << " true";
            }
            else {
                out << " false";
            }
        }
        if (command == "Delete") {
            try {
                if (list.empty()) {
                    throw std::string(" Empty!"); //I seriously appreciate the fact that we can throw things while coding
                }                                    //makes these stupid try/throw/catch statements more bearable.
                list.pop_front();
                out << " OK";
            }
            catch (std::string errorString) {
                out << errorString;
            }
        }
        if (command == "First") {
            try {
                if (list.empty()) {
                    throw std::string(" Empty!");
                }
                out << " " << list.front(); //hate this function
            }
            catch (std::string errorString) {
                out << errorString;
            }
        }
        if (command == "PrintList") {
            try {
                if (list.empty()) {
                    throw std::string(" Empty!");
                }
                out << " " << list;
            }
            catch (std::string errorString) {
                out << errorString;
            }
        }
        if (command == "Remove") {
            iss >> itemsToImport;
            out << " " << itemsToImport;
            list.remove(itemsToImport); //and this one
        }
        if (command == "Reverse") {
            try {
                if (list.empty()) {
                    throw std::string(" Empty!");
                }
                list.reverse();
                out << " OK";
            }
            catch (std::string errorString) {
                out << errorString;
            }
        }
        if (command == "Size") {
            out << " " << list.size();
        }
        if (command == "Last") { //and the extra credit was so not worth the amount of time it took
            try {
                if (list.empty()) {
                    throw std::string(" Empty!");
                }
                out << " " << list.back();
            }
            catch (std::string errorString) {
                out << errorString;
            }
        }
        if (command == "Append") {
            while (iss >> itemsToImport) {
                out << " " << itemsToImport;
                list.push_back(itemsToImport);
            }
        }
        if (command == "Drop") {
            try {
                if (list.empty()) {
                    throw std::string(" Empty!");
                }
                list.pop_back();
                out << " OK";
            }
            catch (std::string errorString) {
                out << errorString;
            }
        }
        out << std::endl;
    }

    //close the files, delete the junk, end the program, chuck the computer
    in.close();
    out.close();
    list.clear();

    return 0;
}
