#include <iostream>

#include "tree/treeContructor.h"
int main() {
    DoubleStack cool;
    cool.pars("l.*a");
    cool.traversal(cool.t.root);
    cool.printFollow();
    cool.printAlphabet();
    cool.printAlphabetMap();
}
