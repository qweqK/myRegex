#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>

class DFA {
    std::map<std::pair<int, char>,int> transitionMap;
    std::set<int> acceptState;
    int startState;
    std::set<char> alphabet;
    std::set<int> allState;
    std::map<std::tuple<int, int, int>, std::string> kPathsCalc;
    public:
    DFA(std::map<std::pair<int, char>,int> &&transitionMap, std::set<int> &&acceptState, int startState, std::set<char> && alphabett) : transitionMap(transitionMap), acceptState(acceptState), startState(startState), alphabet(alphabett) {}
    bool match(const std::string &str);
    std::string kPath();
    std::string recursiveStep(int i, int j, int k);



};
