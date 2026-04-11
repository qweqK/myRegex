#pragma once
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

class DFA {
    std::map<std::pair<int, char>,int> transitionMap;
    std::set<int>   acceptState;
    int startState;
    std::set<char> alphabet;
    std::set<int> allState;
    std::map<std::tuple<int, int, int>, std::string> kPathsCalc;
    std::unique_ptr<DFA> lookAheadDfa;
    bool reachable;
    int trap;
    public:
    DFA(std::map<std::pair<int, char>,int> &&transitionMap, std::set<int> &&acceptState, int startState, std::set<char> && alphabett, int t, std::unique_ptr<DFA> lookDFA=nullptr, bool r=true) : transitionMap(transitionMap), acceptState(acceptState), startState(startState), alphabet(alphabett),trap(t),lookAheadDfa(std::move(lookDFA)), reachable(r) {}
    bool match(const std::string &str);
    std::string kPath();
    std::string recursiveStep(int i, int j, int k);
    void printDFA();
    std::map<std::pair<int, char>,int> &getTransitions() {return transitionMap;}
    std::set<int> &getAcceptStates() {return acceptState;}
    int getStartState() {return startState;}
    std::set<char> getAlphabet() {return alphabet;}
    bool isReachable();
    bool DFS(int i,std::set<int> &visited);
    std::string getInvers(std::string str);
    std::string revRec(std::string);
    void setReachable();
    void deleteUnreachableStates();

    int getTrap() {return trap;}

    void DFS2(int i,std::set<int> &visited);


    bool getReachable() {return reachable;}

};

