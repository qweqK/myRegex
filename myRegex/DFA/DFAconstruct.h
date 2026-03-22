#pragma once
#include <iostream>
#include <memory>
#include <queue>

#include "../tree/treeContructor.h"
//#include ""

// class State {
//     std::string name;
//     std::set<int> pos;
//     int numOFState;
//     bool end;
//     public:
//     int getNumOfState() const {return numOFState;}
//     State () : name("popa"), pos(),end(false), numOFState(0) {};
//     State (std::string &&st, std::set<int> s, int nOFS) : name(st) ,end(false), pos(std::move(s)), numOFState(nOFS) {}
//     std::set<int> &getPos() { return pos; }
//     bool getEnd() const { return end; }
//     bool operator < (const State& other)const {
//         return pos < other.pos;
//     }
//     void setEnd(bool e) {end = e; }
//     void printState() const {
//         std::cout<<name;
//     };
// };

/*class NormalState {
    public:
    int n;
    bool isAccept;
    NormalState() : n(), isAccept(false) {}
    NormalState(int na, bool b) : n(na), isAccept(b) {}
    bool operator < (const NormalState& other)const {
        return n < other.n;
    }
};*/

class DFAConstructor {
    int counter;
    public:
    std::unique_ptr<DoubleStack> d;
    void constructTree(const std::string &str);
    void buildDFA(std::string str);
    //State buildState(std::set<int> &t);
    //std::unique_ptr<NormalState> buildNormalState();
    std::set<int> getUnion(std::set<int>& s, char a);
    //std::map<std::pair<NormalState, char>, NormalState> tableDFA;
    std::map<std::pair<int, char>, int> tableDFA;
    std::vector<std::set<int>> Dstates;
    //std::vector<std::unique_ptr<NormalState>> NormalStates;
    std::set<int> AllStates;
    DFAConstructor(std::unique_ptr<DoubleStack> ds) :d(std::move(ds)), counter(0), Dstates(),tableDFA() {
    }

    std::map<std::set<int>, int> fpTS;
    std::set <int> acceptState;
    void prinStates();
    void printDFA();


    void minimizationDFA();

};
