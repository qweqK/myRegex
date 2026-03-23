#include <iostream>

#include "tree/treeContructor.h"
#include "DFA/DFAconstruct.h"
#include "DFA/DFA.h"
int main() {
    DFAConstructor dc(std::make_unique<DoubleStack>());
    dc.buildDFA("([a-zA-Z]+).( +.-.[a-zA-Z]+)*.( +.[a-zA-Z]+)*. *");
    //dc.buildDFA("(a|b)*.a.b.b");
    dc.d->traversal(dc.d->t.root);
     dc.d->printFollow();
     dc.d->printAlphabet();
     dc.d->printAlphabetMap();
    dc.printDFA();
    std::cout << dc.d->counterPos << std::endl;
    dc.prinStates();

    for (auto f: dc.getAcceptState()) std::cout << f << std::endl;
    //DFAMinimization m(dc.getAcceptState(), dc.getAllStates(), dc.getTable(), dc.d->getAlphabet());
    //m.minimization();
    //DFA q (m.getTable(), m.getAcceptState(), m.getNewStart(), m.getAlphabet());
    DFA q (dc.getTable(), dc.getAcceptState(), 0, std::move(dc.d->alphabet));
    //bool f = q.match("abab");
    bool f = q.match("afs -a f");
    if (f == true) std::cout << "true" << std::endl;
    else std::cout << "false" << std::endl;
}
