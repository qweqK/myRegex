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
    resM.reserve(acceptState.size());
    std::string res;
    std::set<int> alllState;
    for (auto &t : transitionMap) {
        if (!alllState.contains(t.first.first)) alllState.insert(t.first.first);
    }

    for (auto a : acceptState) {
        resM.push_back(recursiveStep(startState+1, a+1, alllState.size()));
    }
    for (auto &s: resM) {
        res.append(s);
        res.push_back('|');
    }
    res.pop_back();
    return res;
}



std::string DFA::recursiveStep(int i, int j, int k) {
    if (kPathsCalc.contains({i,j,k})) return kPathsCalc[{i,j,k}];
    if (k==0) {
        std::set<char> aora;
        std::string res = "";
        for (auto a : alphabet) {
            if (transitionMap[{i-1, a}]==j-1) {
                aora.insert(a);
            }
        }
        for (auto it = aora.begin(); it != aora.end(); ++it) {
            res+=*it;
            if (std::next(it)!=aora.end()) { res.push_back('|');}
        }
        if (i == j) {
            if (res.empty()) res = "$";
            else res = res + "|$";
        }
        if (res.size() > 1) res = "(" + res + ")";
        kPathsCalc[{i,j,k}] = res;
        return res;
    }


    std::string rS1=recursiveStep(i, j, k-1);
    std::string rS2 = recursiveStep(i, k, k-1);
    std::string rS3= recursiveStep(k, k, k-1);
    std::string rS4 = recursiveStep(k, j, k-1);
    std::string res;
    std::string secondPart;
    if (!rS2.empty() && !rS4.empty()) {
        secondPart="(" + rS2 + ")";
        if (!rS3.empty() || rS3 != "$") {
            secondPart.append("(" + rS3 + ")*");
        }
        secondPart.append("("+rS4+")");
    }
    if (!rS1.empty() && !secondPart.empty()) {
        res= "(" + rS1 + "|" + secondPart + ")";
    }
    else if (!secondPart.empty()) {
        res = secondPart;
    }
    else if (!rS1.empty()) {
        res = rS1;
    }
    else res = "";

    kPathsCalc[{i,j,k}] = res;
    return res;
}
