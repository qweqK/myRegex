#include <iostream>

#include "tree/treeContructor.h"
#include "DFA/DFAconstruct.h"
#include "DFA/DFA.h"
#include "regex/mregex.h"
#include  "tree/visualTree.h"
int main() {
   //   DFAConstructor dc(std::make_unique<DoubleStack>());
   //   dc.buildDFA("asv/qa");
   //   //dc.buildDFA("(a|b)*.a.b.b");
   //   dc.d->traversal(dc.d->t.root);
   //    dc.d->printFollow();
   //    dc.d->printAlphabet();
   //    dc.d->printAlphabetMap();
   // saveGraph(dc.d->t.root.get(), "tree.dot");
   //
   //   dc.printDFA();
   //   std::cout << dc.d->counterPos << std::endl;
   //   dc.prinStates();

//
    //  DFAMinimization m(dc.getAcceptState(), dc.getAllStates(), dc.getTable(), dc.d->getAlphabet());
    //  m.minimization();
    // DFA q (m.getTable(), m.getAcceptState(), m.getNewStart(), m.getAlphabet());
    // bool f1 = q.match("asv");
    //  if (f1 == true) std::cout << "true" << std::endl;
    //  else std::cout << "false" << std::endl;

 //mregex regex("([a-zA-Z]+).( +.-.[a-zA-Z]+)*.( +.[a-zA-Z]+)*. *");
  // mregex regex("a(a|b)*");
  // mregex regex("([a-zA-Z]+)( +-[a-zA-Z]+)*( +[a-zA-Z]+)* *");
  // mregex regex2(regex.kPath());
// mregex regex("([abc]+)( +-[abc]+)*( +[abc]+)* *");

    mregex regex("a{,1}");

 bool f = regex.match("");
    //bool g = regex2.match("");
 //std::unique_ptr<DFA> d = r1.diffAutomat(r2);
 //grapGenerate(d->getTransitions(), d->getAcceptStates(), "difAf.dot");
 //d->printDFA();
  if (f == true) std::cout << "true" << std::endl;
  else std::cout << "false" << std::endl;

   /// if (g == true) std::cout << "true" << std::endl;
   /// else std::cout << "false" << std::endl;
}


