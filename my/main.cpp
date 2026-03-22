#include <iostream>

#include "tree/treeContructor.h"
#include "DFA/DFAconstruct.h"
int main() {
    DFAConstructor dc(std::make_unique<DoubleStack>());
    dc.buildDFA("(a|b)*");
    dc.d->traversal(dc.d->t.root);
     dc.d->printFollow();
     dc.d->printAlphabet();
     dc.d->printAlphabetMap();
    dc.printDFA();
    std::cout << dc.d->counterPos << std::endl;
    dc.prinStates();
}
