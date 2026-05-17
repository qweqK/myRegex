#pragma once
#include "../DFA/DFA.h"
#include "../DFA/DFAconstruct.h"
#include  "../DFA/MultiDFA.h"
#include  "../tree/visualTree.h"
#include  "../NFA/NFA.h"
#include "../NFA/constructorNFA.h"

class mregex {
    bool isLookahead = false;
    std::unique_ptr<DFA> dfa;
    std::unique_ptr<NFA> nfa;
    std::unique_ptr<DFA> DFABuilder(std::string re) {
        std::unique_ptr<DFA> dLookahead = nullptr;
        std::pair<std::string, std::string> strs= checkStr(re);

        DFAConstructor dc1(std::make_unique<DoubleStack>());
        dc1.buildDFA(strs.first);
        saveGraph(dc1.d->t.root.get(), "tree.dot");
        std::cout << dc1.d->counterPos << std::endl;
       //dc1.prinStates();
        DFAMinimization m(dc1.getAcceptState(), dc1.getAllStates(), dc1.getTable(), dc1.d->getAlphabet());
        m.minimization();
        if (isLookahead) {
            DFAConstructor dc2(std::make_unique<DoubleStack>());
            dc2.buildDFA(strs.second);
            std::cout << dc2.d->counterPos << std::endl;
            //dc2.prinStates();
            DFAMinimization m2(dc2.getAcceptState(), dc2.getAllStates(), dc2.getTable(), dc2.d->getAlphabet());
            m2.minimization();
            dLookahead= std::make_unique<DFA>(m2.getTable(), m2.getAcceptState(), m2.getNewStart(), m2.getAlphabet(), m2.getTrap());

        }
        return std::make_unique<DFA>(m.getTable(), m.getAcceptState(), m.getNewStart(), m.getAlphabet(),m.getTrap(), std::move(dLookahead));

    }
    std::unique_ptr<NFA> NFABuilder(std::string re) {
        std::pair<std::string, std::string> strs= checkStr(re);
        ConstructorNFA nb;
        return nb.createNFA(re);
    }
public:
    std::pair<std::string, std::string> checkStr(std::string &str);
    mregex(std::unique_ptr<DFA> dfa) : dfa(std::move(dfa))  {};
    mregex(const std::string &re) : dfa(std::move(DFABuilder(re))), nfa(std::move(NFABuilder(re))) {}
    void compile(const std::string &re){ dfa = std::move(DFABuilder(re)), nfa  = std::move(NFABuilder(re)); }
    bool match(const std::string & re) {return dfa->match(re);}
    std::string kPath() {return dfa->kPath();}
    void print() {dfa->printDFA();}
    MultiDFA getMultyAutomat(DFA *other);
    DFA *getDFA() {return dfa.get();}
    bool isEqual(mregex &secRegex);
    mregex diffAutomat(mregex &secRegex);
    void draw(std::string str);
    void drawNFA(const std::string &file) {nfa->graphGenerate(file);}

    void recursiveInvTravers(std::unique_ptr<Node> &n);
    std::string recursiveTraverseToStr(std::unique_ptr<Node> &n);
    std::string invers(std::string str);
    std::string invers();

    void printTrap() {std::cout << dfa->getTrap() << std::endl;}
};
