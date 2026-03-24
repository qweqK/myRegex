#include "DFA.h"

#include <iostream>
#include <ostream>


bool DFA::match(const std::string &str) {
 int currentState=startState;
    for (auto a : str) {
        // std::cout << currentState << " ";
        if (alphabet.contains(a)) currentState = transitionMap[{currentState, a}];
        else {currentState = startState; return false;}
        // std::cout << a << " : "<<currentState << std::endl;

    }

    // for (auto s : acceptState) {
    //     std::cout << s << " ";
    // }
    return acceptState.contains(currentState);
}


std::string DFA::kPath()  {
    std::vector<std::string> resM;
    std::string res;
    for (auto a : acceptState) {
        resM.push_back(recursiveStep(startState, a, allState.size()));
    }
    for (auto &s: resM) {
        res.append(s);
        res.push_back('|');
    }
    res.pop_back();
    return res;
}

std::string DFA::recursiveStep(int i, int j, int k) {
    if (k==0) return "";
    if (kPathsCalc.contains({i,j,k})) return kPathsCalc[{i,j,k}];

    std::string res = "(" + recursiveStep(i, j, k-1) + ")|" (" + recursiveStep(i, k, k-1) + "."+";


}
