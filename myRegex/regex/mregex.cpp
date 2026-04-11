#include "mregex.h"


     MultiDFA mregex::getMultyAutomat(DFA *otherDfa) {

    //std::map<std::pair<std::pair<int,int>, char>, std::pair<int,int>> newTransitions;
    std::map<std::pair<int, char>, int> newTransitions;
    std::map<std::pair<int, int>, int> newAllStates;
    int newFirstState=0;
    std::set<int> allFirstStates;
    std::set<int> allSecondStates;
    std::set<char> alphabet = dfa->getAlphabet();

    for (auto s : otherDfa->getAlphabet()) {
        alphabet.insert(s);
    }
         allFirstStates.insert(dfa->getStartState());
    for (auto &t : dfa->getTransitions()) {
        if (!allFirstStates.contains(t.first.first)) allFirstStates.insert(t.first.first);
    }
         allFirstStates.insert(-1);
         allSecondStates.insert(otherDfa->getStartState());
    for (auto &t : otherDfa->getTransitions()) {
        if (!allSecondStates.contains(t.first.first)) allSecondStates.insert(t.first.first);
    }
         allSecondStates.insert(-1);

    int c=0;
    for (auto &s1 : allFirstStates) {
        for (auto &s2 : allSecondStates) {
            newAllStates.insert({{s1, s2}, c++});
        }
    }
    for (auto &s : newAllStates) {
        for (auto a : alphabet) {
            int n1 = dfa->getTransitions().contains({s.first.first, a}) ? dfa->getTransitions()[{s.first.first, a}] : -1;
            int n2 = otherDfa->getTransitions().contains({s.first.second, a}) ? otherDfa->getTransitions()[{s.first.second, a}] : -1;

                  newTransitions[ {s.second, a} ] = newAllStates[{n1, n2 }];

        }
    }
    for (auto &t : newAllStates) {if (t.first.first == dfa->getStartState() && t.first.second == otherDfa->getStartState()) {newFirstState = t.second; break;}}
    return {newTransitions, newAllStates, newFirstState, alphabet};
}


bool mregex::isEqual(mregex &secRegex) {
         if (isLookahead || secRegex.isLookahead) { throw std::invalid_argument("mregex have lookahead"); }
         //if (dfa->getAlphabet() != secRegex.getDFA()->getAlphabet()) return  false;
         MultiDFA mDFa = getMultyAutomat(secRegex.getDFA());
         std::set<int> newAcceptStates;
         std::map<std::pair<int, int>, int> mAllState = mDFa.getMAllState();
         for (auto &s : mAllState) {
             if (((s.first.first!=-1) && dfa->getAcceptStates().contains(s.first.first)) != ((s.first.second!=-1) && secRegex.getDFA()->getAcceptStates().contains(s.first.second))) {newAcceptStates.insert(s.second);}
         }

         std::unique_ptr<DFA> eqMat = std::make_unique<DFA>(std::move(mDFa.getMTM()), std::move(newAcceptStates), mDFa.getMStart(), std::move(mDFa.getAlphabet()) , dfa->getTrap());
         eqMat->printDFA();
         return !eqMat->isReachable();
}


mregex mregex::diffAutomat(mregex &secRegex) {
    if (isLookahead || secRegex.isLookahead) { throw std::invalid_argument("mregex have lookahead"); }

    MultiDFA mDFa = getMultyAutomat(secRegex.getDFA());
    std::set<int> newAcceptStates;
    std::set<int> AllsStates;
    std::map<std::pair<int, int>, int> mAllState = mDFa.getMAllState();
    for (auto &s : mAllState) {
        AllsStates.insert(s.second);
        std::cout<< s.second << "-> {"<<s.first.first << " " << s.first.second<< "}" << std::endl;
        if (((s.first.first!=-1) && dfa->getAcceptStates().contains(s.first.first)) && !secRegex.getDFA()->getAcceptStates().contains(s.first.second)) {newAcceptStates.insert(s.second);}
    }
         std::cout << "start:" << mDFa.getMStart() << std::endl;
         grapGenerate(mDFa.getMTM(), newAcceptStates, "bfd.dot", mDFa.getMStart());
         DFAMinimization m(std::move(newAcceptStates), std::move(AllsStates), std::move(mDFa.getMTM()), mDFa.getAlphabet(), mDFa.getMStart());
         m.minimization();
         std::unique_ptr<DFA> atm =  std::make_unique<DFA>(m.getTable(), m.getAcceptState(), m.getNewStart(), m.getAlphabet(), m.getTrap());
         atm->setReachable();
         atm->deleteUnreachableStates();
         return atm;
}

std::pair<std::string, std::string> mregex::checkStr(std::string &str) {
    int counter = 0;
    for (int i =0;i < str.size(); ++i) {
        if (str[i] == '(') counter++;
        if (str[i] == ')') counter--;
        if (i > 0 && str[i] == '/' && str[i-1] != '%') {
            if (counter != 0) throw std::runtime_error("syntax error");
            isLookahead = true;
            return std::make_pair(str.substr(0, i), str.substr(i+1, str.size() - 1));
        }
    }
    return std::make_pair(str, "");

}

void mregex::draw(std::string str) {
    grapGenerate(dfa->getTransitions(), dfa->getAcceptStates(), str, dfa->getStartState());
}



void mregex::recursiveInvTravers(std::unique_ptr<Node> &n) {
   if (!n) return;
         recursiveInvTravers(n->_left);
         recursiveInvTravers(n->_right);
         if (n->_nodeType == Node::NodeType::CON) {
             std::unique_ptr<Node> tmp = std::move(n->_left);
             n->_left = std::move(n->_right);
             n->_right = std::move(tmp);
         }
}

std::string mregex::recursiveTraverseToStr(std::unique_ptr<Node> &n) {
         if (!n) return "";
         else if (n->_nodeType == Node::NodeType::A || n->_nodeType == Node::NodeType::Eps) {return std::string(1, n->_data);}
         else if (n->_nodeType == Node::NodeType::CON) { return recursiveTraverseToStr(n->_left)  + recursiveTraverseToStr(n->_right); }
         else if (n -> _nodeType == Node::NodeType::OR) { return "(" + recursiveTraverseToStr(n->_left) + "|" + recursiveTraverseToStr(n->_right) + ")"; }
         else if (n-> _nodeType == Node::NodeType::STAR) { return "(" + recursiveTraverseToStr(n->_left) + ")*" ; }
         else if (n-> _nodeType == Node::NodeType::PLUS) { return "(" + recursiveTraverseToStr(n->_left) + ")+" ; }
         return "";

     }

std::string mregex::invers(std::string str) {
         if (!dfa->getReachable()) throw std::logic_error("automat unreachable");
         DoubleStack d;
         d.pars(str, true);
         recursiveInvTravers(d.t.root);
         return  recursiveTraverseToStr(d.t.root);
}

std::string mregex::invers() {
         if (!dfa->getReachable()) throw std::logic_error("automat unreachable");
         DoubleStack d;
         std::string str = kPath();
         d.pars(str);
         std::unique_ptr<Node> next = std::move(d.t.root->_left);
         recursiveInvTravers(next);
         return  recursiveTraverseToStr(next);
}
