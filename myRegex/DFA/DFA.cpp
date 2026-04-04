#include "DFA.h"

#include <iostream>
#include <ostream>
#include  <array>


bool DFA::match(const std::string &str) {
    if (!lookAheadDfa) {
        int currentState=startState;
        for (auto a : str) {
            if (alphabet.contains(a)) currentState = transitionMap[{currentState, a}];
            else { return false;}
        }

        return acceptState.contains(currentState);
    }
    else {
        int currentState=startState;
        for (int i=0; i<str.length(); i++) {
            if (alphabet.contains(str[i])) currentState = transitionMap[{currentState, str[i]}];
            else {return false;}
        }
    }

}


std::string DFA::kPath()  {
   // if (!lookAheadDfa) throw std::logic_error("DFA with lookahead = bad DFA");
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


void DFA::printDFA() {
    for (auto & s :  transitionMap) {
        std::cout << s.first.first << ": " << s.first.second << "-> "<< s.second;
        if (acceptState.contains(s.first.first)) {std::cout << " true"<< std::endl;}
        else {std::cout << " false"<<std::endl;}
    }
    if (lookAheadDfa){ std::cout << "lookaheadDFA: " << std::endl; lookAheadDfa->printDFA();}
}


bool DFA::isReachable() {
    std::set<int> visited;
    return DFS(startState, visited);
}

bool DFA::DFS(int i, std::set<int> &visited) {
    if (acceptState.contains(i)){ return  true;}
    visited.insert(i);
        for (auto a : alphabet) {
            if (transitionMap.contains({i,a})) {
                int next = transitionMap[{i,a}];
                if (!visited.contains(next)) {
                    if (DFS(next, visited)) return true;
                }
            }
        }

    return false;
}

std::string DFA::getInvers(std::string str) {
    for ()
}
