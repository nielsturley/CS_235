#include <iostream>
#include <fstream>
#include <sstream>
#include "LinkedList.h"

int main(int argc, char* argv[]) {
    //input and output files from command prompt
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);

    LinkedList<std::string> list;

    for (std::string line; getline(in, line);) {
        std::string command, itemsToImport;
        if (line.size() == 0) continue;
        std::istringstream iss(line);
        iss >> command;
        out << command;
        //doing whatever function based on the input ("command") given. I think they are pretty self-explanatory
        try {
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
                if (list.empty()) {
                    throw std::string(" Empty!");
                }
                list.pop_front();
                out << " OK";
            }
            if (command == "First") {
                if (list.empty()) {
                    throw std::string(" Empty!");
                }
                out << " " << list.front();
            }
            if (command == "PrintList") {
                if (list.empty()) {
                    throw std::string(" Empty!");
                }
                out << " " << list;
            }
            if (command == "Remove") {
                iss >> itemsToImport;
                out << " " << itemsToImport;
                list.remove(itemsToImport);
            }
            if (command == "Reverse") {
                if (list.empty()) {
                    throw std::string(" Empty!");
                }
                list.reverse();
                out << " OK";
            }
            if (command == "Size") {
                out << " " << list.size();
            }
            if (command == "Last") {
                if (list.empty()) {
                    throw std::string(" Empty!");
                }
                out << " " << list.back();
            }
            if (command == "Append") {
                while (iss >> itemsToImport) {
                    out << " " << itemsToImport;
                    list.push_back(itemsToImport);
                }
            }
            if (command == "Drop") {
                if (list.empty()) {
                    throw std::string(" Empty!");
                }
                list.pop_back();
                out << " OK";
            }
            if (command == "Iterate") {
                if (list.empty()) {
                    throw std::string(" Empty!");
                }
                LinkedList<std::string>::Iterator iter;
                iter = list.begin();
                while (iter != list.end())
                {
                    out << std::endl << " [" << *iter << "]";
                    ++iter;
                }
            }
            if (command == "Find") {
                iss >> itemsToImport;
                out << " " << itemsToImport;
                LinkedList<std::string>::Iterator position;
                position = list.find(list.begin(), list.end(), itemsToImport);
                out << " OK";
            }
            if (command == "InsertAfter") {
                iss >> itemsToImport;
                out << " " << itemsToImport;
                std::string valueToInsertAfter = itemsToImport;
                iss >> itemsToImport;
                out << " " << itemsToImport;
                std::string valueToFind = itemsToImport;
                LinkedList<std::string>::Iterator position;
                position = list.find(list.begin(), list.end(), valueToFind);
                list.insert_after(position, valueToInsertAfter);
                out << " OK";
            }
            if (command == "InsertBefore") {
                iss >> itemsToImport;
                out << " " << itemsToImport;
                std::string valueToInsertBefore = itemsToImport;
                iss >> itemsToImport;
                out << " " << itemsToImport;
                std::string valueToFind = itemsToImport;
                LinkedList<std::string>::Iterator position;
                position = list.find(list.begin(), list.end(), valueToFind);
                list.insert(position, valueToInsertBefore);
                out << " OK";
            }
            if (command == "Erase") {
                iss >> itemsToImport;
                out << " " << itemsToImport;
                LinkedList<std::string>::Iterator position;
                position = list.find(list.begin(), list.end(), itemsToImport);
                list.erase(position);
                out << " OK";
            }
            if (command == "Replace") {
                iss >> itemsToImport;
                out << " " << itemsToImport;
                std::string oldValue = itemsToImport;
                iss >> itemsToImport;
                out << " " << itemsToImport;
                std::string newValue = itemsToImport;
                list.replace(list.begin(), list.end(), oldValue, newValue);
                out << " OK";
            }
        }
        catch (std::string errorString) {
            out << errorString;
        }
        out << std::endl;
    }

    in.close();
    out.close();

    return 0;
}
