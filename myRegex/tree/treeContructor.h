#pragma once
#include <stack>
#include <string>
#include <map>
#include <unordered_map>

#include "tree.h"
class DoubleStack {
    public:
    std::stack<char> stackOptions;
    std::stack<std::unique_ptr<Node>> nodeStack;
    int counterPos;
    std::map<int, std::set<int>> followPos;
    int getPrior(char c);
    std::set<char> alphabet;
    std::unordered_map<int, char> alphabetMap;
    Tree t;
    //конструкт
    DoubleStack() : counterPos(1) {};
    //парс в дерево сорт стайстион
    void pars(const std::string &input);


    //узло-создатели 3000
    void makeOper(char c);
    void makeAnode(char c);
    void makeOrNode();
    void makeConNode();
    void makeStarNode();
    void makePlusNode();
    void makeEpsilonNode();

    void makeRepeatDiap(std::string &str);
    void makeSymbDiap(std::string &str);

    //проверки 3000
    bool isOperand(char c);
    bool isOperator(char c);

    //отладка 3000
    void traversal(const std::unique_ptr<Node>& node);
    void printFollow();
    void printAlphabet();
    void printAlphabetMap();

    std::set<char> getAlphabet() {return alphabet;};
};




