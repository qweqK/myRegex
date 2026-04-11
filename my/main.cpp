#include <iostream>

#include "tree/treeContructor.h"
#include "DFA/DFAconstruct.h"
#include "DFA/DFA.h"
#include "regex/mregex.h"
#include  "tree/visualTree.h"
int main() {

//
    //  DFAMinimization m(dc.getAcceptState(), dc.getAllStates(), dc.getTable(), dc.d->getAlphabet());
    //  m.minimization();
    // DFA q (m.getTable(), m.getAcceptState(), m.getNewStart(), m.getAlphabet());
    // bool f1 = q.match("asv");
    //  if (f1 == true) std::cout << "true" << std::endl;


    mregex m("a|b|c");
    mregex m2("a|b|c");
    mregex m3(m.diffAutomat(m2));
    mregex m4("g|a|b");
    mregex m5(m4.diffAutomat(m3));
    if (m3.isEqual(m4)) std::cout << "true" << std::endl;
    else std::cout << "false" << std::endl;
    std::cout << m3.kPath() << std::endl;
    m.printTrap();




    m.draw("asa.dot");
    m2.draw("asa2.dot");
    m3.draw("dac.dot");
    m4.draw("ac.dot");
    m5.draw("dacmp.dot");


}


