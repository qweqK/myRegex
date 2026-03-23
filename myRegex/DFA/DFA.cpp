#include "DFA.h"

#include <iostream>
#include <ostream>


bool DFA::match(const std::string &str) {
 int currentState;
    for (auto a : str) {
        if (alphabet.contains(a)) currentState = transitionMap[{currentState, a}];
        else {currentState = startState; return false;}
        std::cout << a << " : "<<currentState << std::endl;

    }
    return acceptState.contains(currentState);
}

