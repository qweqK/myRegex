#include <iostream>

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


   mregex m("[a-f]*|(b)b*");
    m.drawNFA("nfa1.dot");


}


