#pragma once
#include "../DFA/DFA.h"
#include "../DFA/DFAconstruct.h"

class mregex {
    DFA dfa;
    DFA DFABuilder(std::string re) {
        DFAConstructor dc(std::make_unique<DoubleStack>());
        dc.buildDFA(re);
        DFAMinimization m(dc.getAcceptState(), dc.getAllStates(), dc.getTable(), dc.d->getAlphabet());
        m.minimization();
        return DFA(m.getTable(), m.getAcceptState(), m.getNewStart(), m.getAlphabet());
    }
public:
    mregex();
    mregex(std::string re) : dfa(std::move(DFABuilder(re))) {}
    void compile(std::string re){ dfa = std::move(DFABuilder(re));}
    bool match(std::string re) {return dfa.match(re);}

};