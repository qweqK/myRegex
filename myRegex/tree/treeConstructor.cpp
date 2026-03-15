#include <iostream>

#include "treeContructor.h"


int DoubleStack::getPrior(char c) {
    if (c =='|') return 1;
    else if (c== '.') return 2;
    else if (c== '*'|| c== '+') return 3;
    else return 0;

}


void DoubleStack::makeOper(char c) {
    if (c =='|') makeOrNode();
    else if (c =='.') makeConNode();
    else if (c =='*') makeStarNode();
    else if (c =='+') makePlusNode();
}

void DoubleStack::makeAnode(char c) {
    nodeStack.push(std::make_unique<Node>(c, false, std::set<int>{counterPos}, std::set<int>{counterPos}));
    alphabet.insert(c);
    alphabetMap.insert({counterPos++, c});
}

void DoubleStack::makePlusNode() {
    std::unique_ptr<Node> next = std::move(nodeStack.top());
    nodeStack.pop();
    nodeStack.pop();
    std::set<int> lastpos;
    std::set<int> firstpos;
    lastpos.insert(next->_lastpos.begin(), next->_lastpos.end());
    firstpos.insert(next->_firstpos.begin(), next->_firstpos.end());
    for (auto &l : next->_lastpos) {
        followPos[l].insert(next->_firstpos.begin(), next->_firstpos.end());
    }
    nodeStack.push(std::make_unique<Node>('+', next->_nullable, std::move(firstpos), std::move(lastpos), std::move(next), nullptr));

}


void DoubleStack::makeConNode() {
    std::unique_ptr<Node> right = std::move(nodeStack.top());
    nodeStack.pop();
    std::unique_ptr<Node> left = std::move(nodeStack.top());
    nodeStack.pop();
    std::set<int> lastpos;
    std::set<int> firstpos;
    firstpos.insert(left->_firstpos.begin(), left->_firstpos.end());
    if (left->_nullable) {
        firstpos.insert(right->_firstpos.begin(), right->_firstpos.end());
    }
    lastpos.insert(right->_lastpos.begin(), right->_lastpos.end() );
    if (right->_nullable) {
        lastpos.insert(left->_lastpos.begin(), left->_lastpos.end() );
    }
    for (auto &l : left->_lastpos) {
        followPos[l].insert(right->_firstpos.begin(), right->_firstpos.end());
    }
    nodeStack.push(std::make_unique<Node>('.', left->_nullable&&right->_nullable, std::move(firstpos), std::move(lastpos), std::move(left), std::move(right)));


}




void DoubleStack::makeOrNode() {
    std::unique_ptr<Node> right = std::move(nodeStack.top());
    nodeStack.pop();
    std::unique_ptr<Node> left = std::move(nodeStack.top());
    nodeStack.pop();
    std::set<int> lastpos;
    std::set<int> firstpos;
    lastpos.insert(right->_lastpos.begin(), right->_lastpos.end());
    lastpos.insert(left->_lastpos.begin(), left->_lastpos.end());
    firstpos.insert(right->_firstpos.begin(), right->_firstpos.end());
    firstpos.insert(left->_firstpos.begin(), left->_firstpos.end());
    nodeStack.push(std::make_unique<Node>('|', left->_nullable || right->_nullable, std::move(firstpos), std::move(lastpos), std::move(left), std::move(right)));
    
}

void DoubleStack::makeStarNode() {
    std::unique_ptr<Node> next = std::move(nodeStack.top());
    nodeStack.pop();
    std::set<int> lastpos;
    std::set<int> firstpos;
    lastpos.insert(next->_lastpos.begin(), next->_lastpos.end());
    firstpos.insert(next->_firstpos.begin(), next->_firstpos.end());
    for (auto &l : next->_lastpos) {
         followPos[l].insert(next->_firstpos.begin(), next->_firstpos.end());
    }
    nodeStack.push(std::make_unique<Node>('*', true, std::move(firstpos), std::move(lastpos), std::move(next), nullptr));


}


void DoubleStack::pars(const std::string &input) {
    for (char c : input) {
        if(isOperand(c)) {
            makeAnode(c);
        }
        else if (isOperator(c)) {
            while (!stackOptions.empty() && isOperator(stackOptions.top())&& getPrior(stackOptions.top()) >= getPrior(c)) {
                makeOper(stackOptions.top());
                stackOptions.pop();
            }
            stackOptions.push(c);
        }
        else if (c== '(') {
            stackOptions.push('(');
        }
        else if (c== ')') {
            while (!stackOptions.empty() && stackOptions.top() != '(') {
                makeOper(stackOptions.top());
                stackOptions.pop();
            }
            if (stackOptions.empty()) throw std::invalid_argument("skobka problema");
            stackOptions.pop();
        }
    }
    while (!stackOptions.empty() && isOperator(stackOptions.top())) {
        makeOper(stackOptions.top());
        stackOptions.pop();
    }
    if (!stackOptions.empty() && stackOptions.top() == '(') throw std::invalid_argument("skobka problema");

}

void DoubleStack::traversal(const std::unique_ptr<Node>& node) {
    if (!node) return;
    traversal(node->_left);
    traversal(node->_right);
    std::cout<< node->_data<< ' ';
    for (auto& s : node->_firstpos) {std::cout<<s<<" ";}
    std::cout<< ';';
    for (auto& s : node->_lastpos) {std::cout<<s<<" ";}
    std::cout<< ';';
    std::cout<< std::endl;

}

bool DoubleStack::isOperand(char c) {
    if (isOperator(c) || c == '(' || c==')' ) return false;
    else return true;
}

bool DoubleStack::isOperator(char c) {
    if (c=='.' || c== '*' || c== '|' || c== '+') return true;
    else return false;
}

void DoubleStack::printFollow() {
    for (auto &c : followPos ) {
        std::cout << c.first << " | ";
        for (auto f : c.second) {
            std::cout << f << " ";
        }
        std::cout << std::endl;
    }
}


void DoubleStack::printAlphabet() {
    for (char c : alphabet) {
        std::cout << c;
    }
    std::cout << std::endl;
}


void DoubleStack::printAlphabetMap() {
    for (auto &s : alphabetMap) {std::cout << s.first << "-"<< s.second <<std::endl;}
}


