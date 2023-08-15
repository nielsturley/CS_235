#include <iostream>
#include <fstream>
#include <sstream>

#include "QS.h"

int main(int argc, const char * argv[]) {
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);
    
    QS<int> qs;
    
    for (std::string line; getline(in, line);) {
        std::string command, itemToImport;
        if (line.empty()) { continue; }
        std::istringstream iss(line);
        iss >> command;
        out << command;
        try {
            if (command == "QuickSort") {
                iss >> itemToImport;
                qs.clear();
                qs.setCapacity(std::stoi(itemToImport));
                out << " " << itemToImport << " OK" << std::endl;
            }
            if (command == "AddToArray") {
                out << "  ";
                bool first = true;
                while (iss >> itemToImport) {
                    qs.addElement(std::stoi(itemToImport));
                    if (first) {
                        out << itemToImport;
                        first = false;
                    }
                    else { out << "," << itemToImport; }
                }
                out << " OK" << std::endl;
            }
            if (command == "Capacity") {
                out << " " << qs.capacity() << std::endl;
            }
            if (command == "Clear") {
                qs.clear();
                out << " OK" << std::endl;
            }
            if (command == "Size") {
                out << " " << qs.size() << std::endl;
            }
            if (command == "Sort") {
                std::string left, right;
                iss >> left >> right;
                qs.resetCounters();
                qs.sort(std::stoi(left), std::stoi(right));
                out << " " << left << "," << right << " OK" << std::endl;
            }
            if (command == "SortAll") {
                qs.resetCounters();
                qs.sortAll();
                out << " OK" << std::endl;
            }
            if (command == "MedianOfThree") {
                std::string left, right;
                iss >> left >> right;
                int middle = qs.medianOfThree(std::stoi(left), std::stoi(right));
                out << " " << left << "," << right << " = " << middle << std::endl;
            }
            if (command == "Partition") {
                std::string left, right, pivotIndex;
                iss >> left >> right >> pivotIndex;
                int middle = qs.partition(std::stoi(left), std::stoi(right), std::stoi(pivotIndex));
                out << " " << left << "," << right << "," << pivotIndex << " = " << middle << std::endl;
            }
            if (command == "PrintArray") {
                if (qs.size() == 0) { out << " Empty" << std::endl; }
                else { out << " " << qs << std::endl; }
            }
            if (command == "Stats") {
                out << " " << qs.getComparisons() << "," << qs.getExchanges() << std::endl;
            }
        }
        catch (std::string e) { out << e << std::endl; }
    }
    
    in.close();
    out.close();
    return 0;
}
