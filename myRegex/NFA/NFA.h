#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <stack>

using TM = std::multimap<std::pair<int, char>, int>;


class indexesGroup {
  public:
    int firstIdx=-1;
    int lastIdx=-1;
    bool isComplete= false;
    indexesGroup(int f, int l) : firstIdx(f), lastIdx(l) {};
    indexesGroup() : firstIdx(-1), lastIdx(-1) {};
};


class msmatch {
    std::vector<std::string> groups;
public:
    int size = 0;
    std::string operator[] (int i) {
        if (i<0 || i>size) throw std::out_of_range("group zhok ili ne v tu vetke alternative") ;
        return groups[i];
    }
    void fill(std::string &t, std::map<int, indexesGroup> &gm) {
        for (auto i: gm) {
            auto f = i.second;
            if (f.isComplete == true) {
                std::string res = t.substr(f.firstIdx, f.lastIdx - f.firstIdx);
                groups.push_back(res);
            }
            else {
                groups.emplace_back("");
            }
        }
        size = gm.size()-1;
    }
};

class helpContainer {
public:
    int state;
    int strIndx;
    std::map<int, indexesGroup> groupsLoc;
    helpContainer(int s, int si, std::map<int, indexesGroup> g ) : state(s), strIndx(si), groupsLoc(std::move(g)) {};

};

class NFA {
    public:
    TM transitionMap;
    int startState;
    int endStates;
    std::set<int> allStates;
    std::set<char> alphabet;
    std::map<int, int> openGroupsState;
    std::map<int, int> closeGroupsState;
    std::set<int> orStates;


    NFA(int startState, int endStates, std::set<int> allStates, TM transitionMap, std::map<int,int> OGS, std::map<int,int> CGS, std::set<char> a, std::set<int> ors) : startState(startState), endStates(endStates), allStates(std::move(allStates)), transitionMap(std::move(transitionMap)), openGroupsState(std::move(OGS)), closeGroupsState(std::move(CGS)), alphabet(std::move(a)), orStates(std::move(ors)){}
    bool match(std::string t, msmatch &m);
    void graphGenerate(const std::string &outS);

};