#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <stack>

using TM = std::multimap<std::pair<int, char>, int>;

class msmatch {
    std::vector<std::string> groups;
    public:
    int size = 0;
    std::string operator[] (int i) {
        if (i<0 || i>size) return "" ;
            return groups[i];
    }
};

class indexesGroup {
  public:
    int firstIdx;
    int lastIdx;
    bool isComplete;
    indexesGroup(int f, int l) : firstIdx(f), lastIdx(l), isComplete(false) {};
};

class NFA {
    public:
    TM transitionMap;
    int startState;
    int endStates;
    std::set<int> allStates;
    std::set<int> openGroupsState;
    std::set<int> closeGroupsState;
    std::set<char> alphabet;
    std::set<int> curStates;
    std::set<int> orStates;


    std::map<int, indexesGroup> gI;
    std::set<int> nextStates;
    std::set<int> activeGroups;
    std::stack<int> alternativeChoose;
    void makeEpsAction(int &i, int c);

    void makeEpsEndAction(int c);
    void makeSymbAction(int i, int c);


    NFA(int startState, int endStates, std::set<int> allStates, TM transitionMap, std::set<int> OGS, std::set<int> CGS, std::set<char> a, std::set<int> ors) : startState(startState), endStates(endStates), allStates(std::move(allStates)), transitionMap(std::move(transitionMap)), openGroupsState(std::move(OGS)), closeGroupsState(std::move(CGS)), alphabet(std::move(a)), orStates(std::move(ors)){}
    bool match(std::string t, msmatch &m);
    bool reMatch(std::string t, msmatch &m);
    
    std::set<int> getNextState(std::set<int> &curSet);
    void graphGenerate(const std::string &outS);

};