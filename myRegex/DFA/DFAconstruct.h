#pragma once
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>

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
    std::map<std::set<int>, int> fpTS;
    std::set <int> acceptState;

    public:
    std::unique_ptr<DoubleStack> d;
    void constructTree(std::string &str);
    void buildDFA(std::string str);
    //State buildState(std::set<int> &t);
    //std::unique_ptr<NormalState> buildNormalState();
    std::set<int> getUnion(std::set<int>& s, char a);
    //std::map<std::pair<NormalState, char>, NormalState> tableDFA;
    std::map<std::pair<int, char>, int> tableDFA;
    std::vector<std::set<int>> Dstates;
    //std::vector<std::unique_ptr<NormalState>> NormalStates;
    std::set<int> AllStates;
    DFAConstructor(std::unique_ptr<DoubleStack> ds) :d(std::move(ds)), counter(0), Dstates(),tableDFA() {}
    void prinStates();
    void printDFA();


    std::map<std::pair<int, char>, int> &&getTable() { return std::move(tableDFA); }
    std::set<int> &&getAcceptState() { return std::move(acceptState); }
    std::set<int> &&getAllStates() { return std::move(AllStates); }

};

class DFAMinimization {
    std::set<int> AcceptState;
    std::set<int> AllStates;
    std::map<std::pair<int, char>, int> tableDFA;
    std::set<char> alphabet;
    std::vector<std::set<int>> partition;
    std::vector<std::set<int>> newPartitions;
    std::map<int, int> stateToGroup;

    std::map<std::pair<int, char>, int> newTableDFA;
    std::set<int> newAcceptState;
    std::set<int> newAllStates;
    int startState;
    int trap=-1;

    public:
    DFAMinimization(std::set<int> &&AC, std::set<int> && AS,  std::map<std::pair<int, char>, int> &&transition, std::set<char> alphabe, int startState = 0 ) : AcceptState(std::move(AC)), AllStates(std::move(AS)), tableDFA(std::move(transition)), alphabet(std::move(alphabe)), startState(startState) {}
    void minimization();
    void divisionGroup(std::set<int> &G);
    int getGroupIndex(int pos, char a);
    int getNewStart() {return stateToGroup[startState];}
    std::set<int> &&getAcceptState() { return std::move(newAcceptState); }
    std::map<std::pair<int, char>, int> &&getTable() { return std::move(newTableDFA);}
    std::set<char> &&getAlphabet() { return std::move(alphabet);}
    int getTrap() {return trap;}



};


void grapGenerate(const std::map<std::pair<int, char>, int> &transition, const std::set<int> & acceptState,const std::string &outS, int sst);
