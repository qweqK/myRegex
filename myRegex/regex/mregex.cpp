#include "mregex.h"


     MultiDFA mregex::getMultyAutomat(DFA *otherDfa) {

    //std::map<std::pair<std::pair<int,int>, char>, std::pair<int,int>> newTransitions;
    std::map<std::pair<int, char>, int> newTransitions;
    std::map<std::pair<int, int>, int> newAllStates;
    int newFirstState=0;
    std::set<int> allFirstStates;
    std::set<int> allSecondStates;

    for (auto &t : dfa->getTransitions()) {
        if (!allFirstStates.contains(t.first.first)) allFirstStates.insert(t.first.first);
    }
    for (auto &t : otherDfa->getTransitions()) {
        if (!allSecondStates.contains(t.first.first)) allSecondStates.insert(t.first.first);
    }
    int c=0;
    for (auto &s1 : allFirstStates) {
        for (auto &s2 : allSecondStates) {
            newAllStates.insert({{s1, s2}, c++});
        }
    }
    for (auto &s : newAllStates) {
        for (auto a : dfa->getAlphabet()) {
             if (dfa->getTransitions().contains({s.first.first, a}) && otherDfa->getTransitions().contains({s.first.second, a})) {
                 newTransitions[ {s.second, a} ] = newAllStates[{dfa->getTransitions()[{s.first.first, a}], otherDfa->getTransitions()[{s.first.second, a}]  }];
             }
        }
    }
    for (auto &t : newAllStates) {if (t.first.first == dfa->getStartState() && t.first.second == otherDfa->getStartState()) {newFirstState = t.second; break;}}
         for (auto s : newAllStates) {
             std::cout << "{" <<s.first.first << " " << s.first.second << "} -> " <<s.second <<std::endl;
         }
    return {newTransitions, newAllStates, newFirstState};
}


bool mregex::isEqual(mregex &secRegex) {
         if (isLookahead || secRegex.isLookahead) { throw std::invalid_argument("mregex have lookahead"); }
         if (dfa->getAlphabet() != secRegex.getDFA()->getAlphabet()) throw std::invalid_argument("different alphabet");
         MultiDFA mDFa = getMultyAutomat(secRegex.getDFA());
         std::set<int> newAcceptStates;
         std::map<std::pair<int, int>, int> mAllState = mDFa.getMAllState();
         for (auto &s : mAllState) {
             if (dfa->getAcceptStates().contains(s.first.first) && !dfa->getAcceptStates().contains(s.first.second) || !dfa->getAcceptStates().contains(s.first.first) && dfa->getAcceptStates().contains(s.first.second)) {newAcceptStates.insert(s.second);}
         }

         std::unique_ptr<DFA> eqMat = std::make_unique<DFA>(std::move(mDFa.getMTM()), std::move(newAcceptStates), mDFa.getMStart(), dfa->getAlphabet());
         eqMat->printDFA();
         return !eqMat->isReachable();
}


std::unique_ptr<DFA> mregex::diffAutomat(mregex &secRegex) {
    if (isLookahead || secRegex.isLookahead) { throw std::invalid_argument("mregex have lookahead"); }
    if (dfa->getAlphabet() != secRegex.getDFA()->getAlphabet()) throw std::invalid_argument("different alphabet");
    MultiDFA mDFa = getMultyAutomat(secRegex.getDFA());
    std::set<int> newAcceptStates;
    std::map<std::pair<int, int>, int> mAllState = mDFa.getMAllState();
    for (auto &s : mAllState) {
        if (dfa->getAcceptStates().contains(s.first.first) && !dfa->getAcceptStates().contains(s.first.second)) {newAcceptStates.insert(s.second);}
    }

         return std::make_unique<DFA>(std::move(mDFa.getMTM()), std::move(newAcceptStates), mDFa.getMStart(), dfa->getAlphabet());
}





std::pair<std::string, std::string> mregex::checkStr(std::string &str) {
    int counter = 0;
    for (int i =0;i < str.size(); ++i) {
        if (str[i] == '(') counter++;
        if (str[i] == ')') counter--;
        if (str[i] == '/') {
            if (counter != 0) throw std::runtime_error("syntax error");
            isLookahead = true;
            return std::make_pair(str.substr(0, i), str.substr(i+1, str.size() - 1));
        }
    }
    return std::make_pair(str, "");

}



