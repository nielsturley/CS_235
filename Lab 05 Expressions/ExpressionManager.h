#ifndef LAB_05_EXPRESSIONS_EXPRESSIONMANAGER_H
#define LAB_05_EXPRESSIONS_EXPRESSIONMANAGER_H
#include "ExpressionManagerInterface.h"
#include <stack>
#include <vector>
#include <sstream>
#include <algorithm>

//PSYCH I coded 360+ lines in my header file. UGH I need to sleep *sometimes* Dr. Roper.

class ExpressionManager : public ExpressionManagerInterface {
public:
    ExpressionManager() = default;

    ~ExpressionManager() = default;

    //He had a constructor set the expression in the slides, but I had scope issues doing that. So I made a setter instead.
    void setExpression(std::string const& exp) {
        expression_ = exp;
        inFix_.clear();
        preFix_.clear();
        postFix_.clear();
    }

    /** Return the integer value of the infix expression */
    virtual int value(void);

    /** Return the infix items from the expression
        Throw an error if not a valid infix expression as follows:
        First check to see if the expression is balanced ("Unbalanced"),
        then throw the appropriate error immediately when an error is found
        (ie., "Missing Operand", "Illegal Operator", "Missing Operator") */
    virtual std::string infix(void);

    /** Return a postfix representation of the infix expression */
    virtual std::string postfix(void);

    void processOperatorPostfix(std::string const& operator_, std::stack<std::string>& stack, std::vector<std::string>& postFix_) const;

    /** Return a prefix representation of the infix expression */
    virtual std::string prefix(void);

    void processOperatorPrefix(std::string const& operator_, std::stack<std::string>& stack, std::vector<std::string>& preFix_) const;

    /** Return the infix vector'd expression items */
    virtual std::string toString(void) const {
        std::string out;
        for (unsigned int i = 0; i < inFix_.size(); ++i) {
            out += " " + inFix_.at(i);
        }
        return out;
    }

    friend std::ostream& operator<< (std::ostream& os, const ExpressionManager& exp) {
        os << exp.toString(); //I feel like I'm friends with my class too...after all this time we've spent together...
        return os;
    }

    bool isLeftParen(const std::string& t) const {
        if (t == "(" || t == "[" || t == "{") {
            return true;
        }
        else {
            return false;
        }
    }

    bool isRightParen(const std::string& t) const {
        if (t == ")" || t == "]" || t == "}") {
            return true;
        }
        else {
            return false;
        }
    }

    bool isPair(std::string const& left, std::string const& right) const {
        if (left == "(" && right == ")") {
            return true;
        }
        if (left == "[" && right == "]") {
            return true;
        }
        if (left == "{" && right == "}") {
            return true;
        }
        return false;
    }

    bool isOperator(std::string t) {
        if (OPERATORS.find(t) != std::string::npos) { //had this backwards. my first debug on this lab. *wipes tear away*
            return true;
        }
        else {
            return false;
        }
    }

    bool isOperand(std::string t) {
        for (unsigned int i = 0; i < t.size(); ++i) {
            if (!isdigit(t.at(i))) {
                return false;
            }
        }
        return true;
    }

    int precedence(std::string const& operator_) const {
        if (operator_ == "*" || operator_ == "/" || operator_ == "%") {
            return 2;
        }
        if (operator_ == "+" || operator_ == "-") {
            return 1;
        }
        if (isLeftParen(operator_) || isRightParen(operator_)) {
            return 0;
        }
        throw std::string(" Illegal Operator"); //yeah, so this isn't totally accurate, but what else? return a three? I already error checked everything.
    }

private:
    std::string expression_;
    std::vector<std::string> inFix_;
    std::vector<std::string> postFix_;
    std::vector<std::string> preFix_;
    const std::string OPERATORS = "-+*/%";

};



#endif //LAB_05_EXPRESSIONS_EXPRESSIONMANAGER_H
