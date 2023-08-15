#include <iostream>
#include <fstream>
#include "ExpressionManager.h"

//Oh yes. A mere 50 lines for main.cpp. Must've been *such* an easy lab. Took *no* effort at all.
int main(int argc, char* argv[]) {
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);

    string line, command;
    ExpressionManager expression;
    //basic get-your-line, do-your-job crap
    while (getline(in, line)) {
        try {
            if (line.size() == 0) continue;
            std::istringstream iss(line);
            iss >> command;
            if (command == "Expression:") {
                out << std::endl;
                out << line;
                std::string exp;
                getline(iss, exp);
                expression.setExpression(exp);
            }
            else if (command == "Infix:") {
                out << command;
                out << expression.infix();
            }
            else if (command == "Prefix:") {
                out << command;
                out << expression.prefix();
            }
            else if (command == "Postfix:") {
                out << command;
                out << expression.postfix();
            }
            else if (command == "Value:") {
                out << command;
                out << " " << expression.value();
            }
        }
        catch (std::string& e) {
            out << e;
        }
        out << std::endl;
    }

    in.close();
    out.close();
}