#include <iostream>

#include "tree/treeContructor.h"
#include "DFA/DFAconstruct.h"
#include "DFA/DFA.h"
#include "regex/mregex.h"
int main() {
//     DFAConstructor dc(std::make_unique<DoubleStack>());
//     dc.buildDFA("([a-zA-Z]+).( +.-.[a-zA-Z]+)*.( +.[a-zA-Z]+)*. *");
//     //dc.buildDFA("(a|b)*.a.b.b");
//     dc.d->traversal(dc.d->t.root);
//      dc.d->printFollow();
//      dc.d->printAlphabet();
//      dc.d->printAlphabetMap();
//     dc.printDFA();
//     std::cout << dc.d->counterPos << std::endl;
//     dc.prinStates();
//
//     DFAMinimization m(dc.getAcceptState(), dc.getAllStates(), dc.getTable(), dc.d->getAlphabet());
//     m.minimization();
//     DFA q (m.getTable(), m.getAcceptState(), m.getNewStart(), m.getAlphabet());
//    // DFA q (dc.getTable(), dc.getAcceptState(), 0, std::move(dc.d->alphabet));
//     //bool f = q.match("abaaabb");
//     bool f = q.match("");
//     if (f == true) std::cout << "true" << std::endl;
//     else std::cout << "false" << std::endl;
    mregex regex("([a-zA-Z]+).( +.-.[a-zA-Z]+)*.( +.[a-zA-Z]+)*. *");
    bool f = regex.match("asdd -d -f qa");
    if (f == true) std::cout << "true" << std::endl;
    else std::cout << "false" << std::endl;
    regex.compile("r.e.g.e.x*");
    //f= regex.match("regexxxxx");
    if (f == true) std::cout << "true" << std::endl;
    else std::cout << "false" << std::endl;
}


