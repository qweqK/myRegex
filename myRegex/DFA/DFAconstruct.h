#pragma once
#include <memory>
#include "../tree/treeContructor.h"
//#include ""
class DFAConstructor {
    DoubleStack d;
    public:
    DFAConstructor();
    void constructTree(const std::string &str);
    void buildDFA();

};



class State {
    public:
    std::string name;

};