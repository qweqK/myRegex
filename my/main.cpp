#include <iostream>

#include "tree/treeContructor.h"
#include "tree/visualTree.h"
int main() {
    DoubleStack cool;
    cool.pars("(l|d)*.[a-c].v");
    cool.traversal(cool.t.root);
    cool.printFollow();
    cool.printAlphabet();
    cool.printAlphabetMap();
    saveGraph(cool.t.root.get(), "tree.dot");
}
