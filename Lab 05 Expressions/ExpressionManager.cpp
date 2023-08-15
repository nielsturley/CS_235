#include "ExpressionManager.h"

void ExpressionManager::processOperatorPrefix(const string &operator_, std::stack<std::string> &stack,
                                              std::vector<std::string> &preFix_) const {
    if (stack.empty() || isLeftParen(operator_)) {
        stack.push(operator_);
    }
    else {
        if (precedence(operator_) >= precedence(stack.top())) { //this time it's greater or equal to. Like I said, no idea why, but it works.
            if (isLeftParen(stack.top()) && isRightParen(operator_)) { //THIS nasty little bugger was the LAST thing I had to do for this lab. Good riddance.
                stack.pop();
            }
            else {
                stack.push(operator_);
            }
        }
        else {
            while (!stack.empty() && !isLeftParen(stack.top()) && (precedence(operator_) < precedence(stack.top()))) {
                preFix_.push_back(stack.top());
                stack.pop();
            }
            if (isRightParen(operator_)) {
                stack.pop();
            }
            else {
                stack.push(operator_);
            }
        }
    }
}

std::string ExpressionManager::prefix(void) {
    //why does this have to be so much more complicated??
    //it's functions like these that make me question why I'm doing computer science stuff
    //as a neuroscience major
    if (inFix_.empty()) {
        infix();
    }
    std::vector<std::string> tempPreFix_ = inFix_; //so we have a temporaryPreFix here, not a real one.
    std::reverse(tempPreFix_.begin(), tempPreFix_.end()); //GODSEND FUNCTION I hate figuring out the reverse vector junk
    for (unsigned int i = 0; i < tempPreFix_.size(); ++i) {
        if (isLeftParen(tempPreFix_.at(i))) {
            if (tempPreFix_.at(i) == "(") {
                tempPreFix_.at(i) = ")";
            }
            if (tempPreFix_.at(i) == "[") {
                tempPreFix_.at(i) = "]";
            }
            if (tempPreFix_.at(i) == "{") {
                tempPreFix_.at(i) = "}";
            }
        }
        else if (isRightParen(tempPreFix_.at(i))) { //originally had this as just "if"
            if (tempPreFix_.at(i) == ")") {         //took me, hmm, 25 minutes to figure out why my parenthesis kept
                tempPreFix_.at(i) = "(";            //switching back
            }
            if (tempPreFix_.at(i) == "]") {
                tempPreFix_.at(i) = "[";
            }
            if (tempPreFix_.at(i) == "}") {
                tempPreFix_.at(i) = "{";
            }
        }
    }
    std::stack<std::string> stack;
    for (unsigned int i = 0; i < tempPreFix_.size(); ++i) {
        if (isOperand(tempPreFix_.at(i))) {
            preFix_.push_back(tempPreFix_.at(i)); //taking stuff from the tempPreFix into preFix because
        }                                         //moving all the stuff in tempPreFix itself would be a nightmare
        else {
            processOperatorPrefix(tempPreFix_.at(i), stack, preFix_); //look! Another magic function.
        }
    }
    while (!stack.empty()) {
        preFix_.push_back(stack.top());
        stack.pop();
    }
    std::reverse(preFix_.begin(), preFix_.end()); //you reverse it...then reverse it back...
    std::string out;
    for (unsigned int i = 0; i < preFix_.size(); ++i) {
        out += " " + preFix_.at(i);
    }
    return out;
}

void ExpressionManager::processOperatorPostfix(const string &operator_, std::stack<std::string> &stack,
                                               std::vector<std::string> &postFix_) const {
    //This is the magic function
    //It's magic because I'm still not quite sure how it works
    //But it works
    //So
    //Yeah
    if (stack.empty() || isLeftParen(operator_)) {
        stack.push(operator_);
    }
    else {
        if (precedence(operator_) > precedence(stack.top())) {
            stack.push(operator_);
        }
        else { //like honestly I pretty much took this verbatim from the textbook. I mean, I could figure it out, but it's midnight and my brain says no.
            while (!stack.empty() && !isLeftParen(stack.top()) && (precedence(operator_) <= precedence(stack.top()))) {
                postFix_.push_back(stack.top());
                stack.pop();
            }
            if (isRightParen(operator_)) {
                stack.pop();
            }
            else {
                stack.push(operator_);
            }
        }
    }
}

int ExpressionManager::value(void) {
    if (postFix_.empty()) { //this little check right here gave me about an half an hour's worth of trouble
        postfix();
    }
    std::stack<int> stack;
    for (unsigned int i = 0; i < postFix_.size(); ++i) {
        if (isOperand(postFix_.at(i))) {
            stack.push(stoi(postFix_.at(i))); //Please observe my fancy stoi function which magically changes my string into an int.
        }                                            //I found out stoi existed, hmm, just about 30 minutes ago.
        if (isOperator(postFix_.at(i))) {         //*bangs head against the wall*
            int right = stack.top();
            stack.pop();
            int left = stack.top();
            stack.pop();
            if (postFix_.at(i) == "-") {     //Lemme get this straight. All we were supposed to do in this lab
                stack.push(left - right); //is do something the computer already knows how to do.
            }                                //Right?
            if (postFix_.at(i) == "+") {     //Wow.
                stack.push(left + right); //Yippee.
            }
            if (postFix_.at(i) == "*") {
                stack.push(left * right);
            }
            if (postFix_.at(i) == "/") {
                stack.push(left / right);
            }
            if (postFix_.at(i) == "%") {
                stack.push(left % right);
            }
        }
    }
    return stack.top();
}

std::string ExpressionManager::infix(void) {
    std::stack<std::string> stack;
    std::istringstream iss(expression_);
    std::string next;

    //Unbalanced checking. Puts parentheses onto stack, pops 'em off if they match
    //If they don't match or if the stack isn't empty by the end it throws unbalanced.
    while (iss >> next) {
        if (isLeftParen(next)) {
            stack.push(next);
        }
        if (isRightParen(next)) {
            if (!stack.empty()) { //<----when you get FULL POINTS on the lab and then stupid valgrind says
                if (isPair(stack.top(), next)) { //"hehe you have a random uninitialized value in your code sucks to be you"
                    stack.pop();                 //"where you ask? No idea good luck finding it." *chucks the computer*
                }
            }
            else {
                throw std::string(" Unbalanced");
            }
        }
    }
    if (!stack.empty()) {
        throw std::string(" Unbalanced");
    }

    //So I'm pretty sure I overcompensated for some errors that I didn't need to check for,
    //But I dunno I got OCD triggered or something.
    iss.str(expression_);
    iss.clear();
    while (iss >> next) {
        if (stack.empty()) { //special empty stack case
            if (isOperand(next) || isLeftParen(next)) {
                inFix_.push_back(next);
                stack.push(next); //I guess I could've just used the vector.end() instead of stack.
            }                     //But I'm too lazy.
            else {
                throw std::string(" Missing Operand");
            }
        }
        else { //5 options available: operator, operand, left paren, right paren, or illegal operator.
            if (isOperator(next)) {
                if (isOperand(stack.top()) || isRightParen(stack.top())) { //basic format is "if (good things to have on the left of next)"
                    inFix_.push_back(next);                                 //do this junk
                    stack.push(next);
                }
                else {                                                  //else throw the respective error
                    throw std::string(" Missing Operand");
                }
            }
            else if (isOperand(next)) {
                if (isOperator(stack.top()) || isLeftParen(stack.top())) {
                    inFix_.push_back(next);
                    stack.push(next);
                }
                else {
                    throw std::string(" Missing Operator");
                }
            }
            else if (isLeftParen(next)) {
                if (isOperator(stack.top()) || isLeftParen(stack.top())) {
                    inFix_.push_back(next);
                    stack.push(next);
                }
                else {
                    throw std::string(" Missing Operator");
                }
            }
            else if (isRightParen(next)) {
                if (isOperand(stack.top()) || isRightParen(stack.top())) {
                    inFix_.push_back(next);
                    stack.push(next);
                }
                else {
                    throw std::string(" Missing Operand");
                }
            }
            else {
                throw std::string(" Illegal Operator");
            }
        }
    }
    if (isOperator(stack.top()) || isLeftParen(stack.top())) { //bad things to have at the end of the expression
        throw std::string(" Missing Operand");
    }
    return toString();
}

std::string ExpressionManager::postfix(void) {
    if (inFix_.empty()) {
        infix();
    }
    std::stack<std::string> stack;
    for (unsigned int i = 0; i < inFix_.size(); ++i) { //I get it. PostFix is cool. Whatever.
        if (isOperand(inFix_.at(i))) {              //Still don't think I'll ever use it after this class
            postFix_.push_back(inFix_.at(i));
        }
        else {
            processOperatorPostfix(inFix_.at(i), stack, postFix_);
        }
    }
    while (!stack.empty()) {
        postFix_.push_back(stack.top());
        stack.pop();
    }
    std::string out;
    for (unsigned int i = 0; i < postFix_.size(); ++i) {
        out += " " + postFix_.at(i);
    }
    return out;
}