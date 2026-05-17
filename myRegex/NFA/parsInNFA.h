#pragma once
#include <map>
#include <memory>
#include <set>
#include <stack>
#include <iostream>

enum class NNType { A, Eps, OR, STAR, CON, PLUS, CB};

class NNode {
    public:
    NNType type;
    std::unique_ptr<NNode> _left;
    std::unique_ptr<NNode> _right;
    char _data;
    int counterVertex=0;
    NNode(NNType type, char data, std::unique_ptr<NNode> left = nullptr, std::unique_ptr<NNode> right = nullptr) : type(type), _left(std::move(left)), _right(std::move(right)), _data(data) {}
    NNode(NNType type, char data, std::unique_ptr<NNode> next, int gn ) : type(type), _left(std::move(next)), _right(nullptr), _data(data), groupNumb(gn) {}
    NNType getType() const { return type; }
    int groupNumb = -1;


};

class parsInNFA {
    public:
    std::unique_ptr<NNode> root = nullptr;
    std::stack<char> stackOptions;
    std::stack<std::unique_ptr<NNode>> nodeStack;
    std::set<char> alphabet;
    int capNumb = 0;
    int getPrior(char c);
    void makeOper(char c);
    void makeAnode(char c);
    void makeOrNode();
    void makeConNode();
    void makeStarNode();
    void makePlusNode();
    void makeEpsilonNode();
    void makeCBNode();
    void pars(std::string &input);

    void makeRepeatDiap(std::string &str);
    void makeSymbDiap(std::string &str);

    //проверки 3000
    bool isOperand(char c);
    bool isOperator(char c);
    bool isForCon(char c);


    void chooseMakeNode(char, NNType nt);
    void traversClone(const std::unique_ptr<NNode>& node);
    void takeSmartCopyNode(const std::unique_ptr<NNode>& node);



};
