#pragma once
#include <memory>
#include <queue>

#include "../tree/treeContructor.h"
//#include ""

class State {
public:
    std::string name;
    bool end;

};

class DFAConstructor {
    DoubleStack d;
    public:
    void constructTree(const std::string &str);
    void buildDFA();
    std::unordered_map<std::pair<State, char>, State> table;
    std::queue<State> states;
    std::set<State> processedStates;



};
