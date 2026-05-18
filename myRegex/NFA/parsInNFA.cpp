
#include "parsInNFA.h"

void parsInNFA::pars(std::string &input) {
    if (input.empty()) {
        makeAnode('#');
        root = std::move(nodeStack.top());
        alphabet.erase('#');
        return;
    }
    std::string newStr;
    newStr.push_back('(');
    for (auto c = input.begin(); c != input.end(); c++) {
        newStr.push_back(*c);
        //std::cout << *c << std::endl;
        if ( (isOperand(*c) || *c == ')' || *c == ']' || *c == '}' || *c=='*' || *c == '+'|| *c == '[' || *c == '$') && std::next(c) != input.end() && (isOperand(*std::next(c)) || *std::next(c) == '$' || *std::next(c)== '(' || *std::next(c) == '%' ||*std::next(c) == '[' || *std::next(c) == '{' || *std::next(c)== '\\')) {
            if (*c == '[' || *std::next(c) == '[') {
                if (*c != '[') newStr.push_back('.');
                c++;
                while (c != input.end() && *std::next(c) != ']') {newStr.push_back(*c); c++; }
                if (c == input.end()) throw std::invalid_argument("problema []");
                newStr.push_back(*c);
                continue;
            }
            else if (*std::next(c) == '{') {
                c++;
                while (c != input.end() && *std::next(c) != '}') {newStr.push_back(*c); c++; }
                if (c == input.end()) throw std::invalid_argument("problema {}");
                newStr.push_back(*c);
                continue;
            }


            //else if (*std::next(c) == '%')

            newStr.push_back('.');
        }
        else if (*c == '%'  && std::next(c) != input.end()) {
            std::cout << *c << std::endl;
            c++;
            newStr.push_back(*c);
            if (std::next(c)!= input.end() && ( *std::next(c)!= ')' || *std::next(c) == ']' || *std::next(c) == '}' )) newStr.push_back('.');
        }
        else if (*c == '\\'  && std::next(c) != input.end()) {
            std::cout << *c << std::endl;
            c++;
            newStr.push_back(*c);
            std::cout << newStr << std::endl;
            if (std::next(c)!= input.end() && ( isOperand(*std::next(c)) )) newStr.push_back('.');
            std::cout << newStr << std::endl;
        }

    }
    newStr.append(")");
    std::cout << newStr << std::endl;
    for (auto c = newStr.begin(); c != newStr.end(); c++) {
        if(isOperand(*c)) {
            makeAnode(*c);
        }

        else if (*c == '%') makeAnode(*(++c));
        else if (*c == '\\') {std::string curS({*(++c)}); makeNGNode(std::stoi(curS));}
        else if (*c == '[') {
            c++;
            std::string tmp;
            while (c != input.end() && *c != ']') {
                tmp.push_back(*(c++));
            }
            if (c == input.end()) throw std::invalid_argument("problema []");
            makeSymbDiap(tmp);
        }
        else if (*c == '{') {
            c++;
            std::string tmp;
            while (c != input.end() && *c != '}') {
                tmp.push_back(*(c++));
            }
            if (c == input.end()) throw std::invalid_argument("problema {}");
            makeRepeatDiap(tmp);
        }
        else if (*c == '$') makeEpsilonNode();
        else if (*c == '*') makeStarNode();
        else if (*c == '+') makePlusNode();


        else if (isOperator(*c)) {
            while (!stackOptions.empty() && isOperator(stackOptions.top())&&getPrior(stackOptions.top()) >= getPrior(*c)) {
                makeOper(stackOptions.top());
                stackOptions.pop();
            }

            stackOptions.push(*c);
        }
        else if (*c== '(') {
            stackOptions.push('(');
            groupIdx.push(capNumb);
            capNumb++;

        }
        else if (*c== ')') {
            while (!stackOptions.empty() && stackOptions.top() != '(') {
                makeOper(stackOptions.top());
                stackOptions.pop();
            }
            makeCBNode();
            if (stackOptions.empty()) throw std::invalid_argument("skobka problema");
            stackOptions.pop();
        }
    }
    while (!stackOptions.empty() && isOperator(stackOptions.top())) {
        makeOper(stackOptions.top());
        stackOptions.pop();
    }
    if (!stackOptions.empty() && stackOptions.top() == '(') throw std::invalid_argument("skobka problema");
    root = std::move(nodeStack.top());
}

int parsInNFA::getPrior(char c) {
    if (c =='|') return 1;
    else if (c== '.') return 2;
    else if (c== '*'|| c== '+') return 3;
    else return 0;

}


void parsInNFA::makeRepeatDiap(std::string &str) {
    if (str.empty()) throw std::invalid_argument("problema {qwee}");
    size_t pos = str.find_first_of(',');
    int n1=0, n2=0;
    std::cout << str << std::endl;
    if (pos != std::string::npos) {
        std::string sn1 = str.substr(0, pos);
        std::string sn2 = str.substr(pos+1, str.size());
        if (!sn1.empty()) n1 = std::stoi(sn1);
        if (!sn2.empty()) n2 = std::stoi(sn2);
        std::unique_ptr<NNode> a = std::move(nodeStack.top());
        nodeStack.pop();
        if (sn2.empty()) {
            makeEpsilonNode();
            //nodeStack.push(std::move(a->clone()));
            for (int i = 0; i < n1; i++) {
                takeSmartCopyNode(a);
                makeConNode();
            }
            takeSmartCopyNode(a);
            makeStarNode();
            makeConNode();
        }
        else if (!sn2.empty()) {
            if (n1>n2) throw std::invalid_argument("n1 >n2 {}");
            bool firstCreate = false;

            for (int i = n1; i < n2+1; i++) {
                makeEpsilonNode();
                for (int j = 0; j < i; j++) {
                    takeSmartCopyNode(a);
                    makeConNode();
                }
                if (firstCreate) { makeOrNode();}
                firstCreate = true;
            }
        }

    }
    else {
        throw std::invalid_argument("problema {}");
    }
}


void parsInNFA::makeSymbDiap(std::string &str) {
   if (str.empty()) return;
    bool firstNodeCreat = false;
    for (auto it = str.begin(); it != str.end(); it++) {
        if (std::next(it) != str.end() && *std::next(it) == '-' && std::next(it,2) != str.end()) {
            char c1= *it;
            char c2= *std::next(it,2);
            if ( c1> c2) throw std::invalid_argument("problema [c1>c2]");
           for (int i=c1; i<=c2; i++) {
               makeAnode(i);
               if (firstNodeCreat) {
                   makeOrNode();
               }
               firstNodeCreat = true;
           }
            std::advance(it,2);
        }

        else {
            makeAnode(*it);
            if (firstNodeCreat) {
                makeOrNode();
            }
            firstNodeCreat = true;
        }
    }

}



bool parsInNFA::isOperand(char c) {
    if (isOperator(c) || c == '(' || c==')' || c== '%'|| c== '[' || c== ']' || c=='{'|| c=='}' || c == '$' || c == '\\') return false;
    else return true;
}

bool parsInNFA::isOperator(char c) {
    if (c=='.' || c== '*' || c== '|' || c== '+') return true;
    else return false;
}

bool parsInNFA::isForCon(char c) {
    if (isOperand(c) || c=='(' || c == ')') return true;
    else return false;
}


void parsInNFA::takeSmartCopyNode(const std::unique_ptr<NNode>& node) {
    traversClone(node);
}

void parsInNFA::traversClone(const std::unique_ptr<NNode>& node) {
    if (!node) return;
    traversClone(node->_left);
    traversClone(node->_right);
    chooseMakeNode(node->_data, node->type,  node->groupNumb);
}

void parsInNFA::chooseMakeNode(char c, NNType t, int g) {
    switch (t) {
        case NNType::A : {makeAnode(c);} break;
        case NNType::Eps : {makeEpsilonNode();} break;
        case NNType::OR : {makeOrNode();} break;
        case NNType::CON : {makeConNode();} break;
        case NNType::PLUS : {makePlusNode();} break;
        case NNType::STAR : {makeStarNode();} break;
        case NNType::CB : {makeEmptyNode();} break;
        case NNType::NG : {makeNGNode(g);}
        default: throw std::invalid_argument("problemas");

    }
}


void parsInNFA::makeAnode(char c) {
    nodeStack.push(std::make_unique<NNode>( NNType::A, c));
    alphabet.insert(c);
}

void parsInNFA::makeEpsilonNode() {
    nodeStack.push(std::make_unique<NNode>( NNType::Eps, '$'));
}
void parsInNFA::makeOrNode() {
    if (nodeStack.size()<2) throw std::invalid_argument("oper | prob");
    std::unique_ptr<NNode> right = std::move(nodeStack.top());
    nodeStack.pop();
    std::unique_ptr<NNode> left = std::move(nodeStack.top());
    nodeStack.pop();
    nodeStack.push(std::make_unique<NNode>(NNType::OR, '|' ,std::move(left), std::move(right)));

}

void parsInNFA::makeNGNode(int  c) {
    if (!alreadyExistsGroup.contains(c)) throw std::invalid_argument("group " + std::to_string(c) + " not Exist");
    nodeStack.push(std::make_unique<NNode>(NNType::NG, '\\' , nullptr, c));
}


void parsInNFA::makeOper(char c) {
    if (c =='|') makeOrNode();
    else if (c =='.') makeConNode();
    else if (c =='*') makeStarNode();
    else if (c =='+') makePlusNode();
}

void parsInNFA::makeConNode() {
    if (nodeStack.size()<2) throw std::invalid_argument("oper . prob");
    std::unique_ptr<NNode> right = std::move(nodeStack.top());
    nodeStack.pop();
    std::unique_ptr<NNode> left = std::move(nodeStack.top());
    nodeStack.pop();
    nodeStack.push(std::make_unique<NNode>(NNType::CON, '.' ,std::move(left), std::move(right)));
}


void parsInNFA::makePlusNode() {
    if (nodeStack.empty()) throw std::invalid_argument("oper + prob");
    std::unique_ptr<NNode> next = std::move(nodeStack.top());
    nodeStack.pop();
    nodeStack.push(std::make_unique<NNode>(NNType::PLUS, '+' ,std::move(next)));
}
void parsInNFA::makeStarNode() {
    if (nodeStack.empty()) throw std::invalid_argument("oper * prob");
    std::unique_ptr<NNode> next = std::move(nodeStack.top());
    nodeStack.pop();
    nodeStack.push(std::make_unique<NNode>(NNType::STAR, '*' ,std::move(next)));
}

void parsInNFA::makeCBNode() {
    if (nodeStack.empty()) throw std::invalid_argument("oper () prob");
    std::unique_ptr<NNode> next = std::move(nodeStack.top());
    nodeStack.pop();
    nodeStack.push(std::make_unique<NNode>(NNType::CB, '(' ,std::move(next), groupIdx.top()));
    alreadyExistsGroup[groupIdx.top()] = true;
    groupIdx.pop();
}

void parsInNFA::makeEmptyNode() {
    if (nodeStack.empty()) throw std::invalid_argument("oper () prob");
    std::unique_ptr<NNode> next = std::move(nodeStack.top());
    nodeStack.pop();
    nodeStack.push(std::make_unique<NNode>(NNType::EMPTY, 'e' ,std::move(next), groupIdx.top()));
}


