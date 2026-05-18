#include <iostream>
#include <regex>
#include "tree/treeContructor.h"
#include "DFA/DFAconstruct.h"
#include "DFA/DFA.h"
#include "regex/mregex.h"
#include  "tree/visualTree.h"
int main() {

    //  DFAMinimization m(dc.getAcceptState(), dc.getAllStates(), dc.getTable(), dc.d->getAlphabet());
    //  m.minimization();
    // DFA q (m.getTable(), m.getAcceptState(), m.getNewStart(), m.getAlphabet());
    // bool f1 = q.match("asv");
    //  if (f1 == true) std::cout << "true" << std::endl;

    msmatch msm;
   mregex m("(a*a*(a*a*)\\2)\\1b\\2");
    m.drawNFA("nfa1.dot");
    bool res = m.match("aaaaba",msm);
     if (res) {
         std::cout << "true"<< std::endl;
         std::cout << msm[0] << '\n' <<msm[1] << '\n' <<msm[2] << std::endl;
    }
     else std::cout << "false"<< std::endl;
}


