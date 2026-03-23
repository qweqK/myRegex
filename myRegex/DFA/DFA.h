#pragma once
#include <map>
#include <set>
#include <string>

class DFA {
    std::map<std::pair<int, char>,int> transitionMap;
    std::set<int> acceptState;
    int startState;
    std::set<char> alphabet;
    public:
    DFA(std::map<std::pair<int, char>,int> &&transitionMap, std::set<int> &&acceptState, int startState, std::set<char> && alphabett) : transitionMap(transitionMap), acceptState(acceptState), startState(startState), alphabet(alphabett) {}
    bool match(const std::string &str);


};
