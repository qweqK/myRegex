#include "tree/treeContructor.h"

int main() {
    DoubleStack cool;
    cool.pars("(a|b)*.v*.n.#");
    cool.traversal(cool.nodeStack.top());
    cool.printFollow();
    cool.printAlphabet();
    cool.printAlphabetMap();
}
