#include "NFA.h"


std::set<int> NFA::getNextState(std::set<int> &curSet) {


}


bool NFA::match(std::string t, msmatch &m) {

}



void NFA::graphGenerate(const std::string &outS) {

    std::set<int> acceptState={endStates};
    int sst = startState;
    TM transition = transitionMap;

    std::ofstream ss(outS);
    ss << "digraph automat {\n";
    ss << "    rankdir=LR;\n";
    ss << "    size=\"8,5\";\n";
    if (!acceptState.contains(sst)) {
        ss << "    node [shape = square];\n";
    }
    else ss << "    node [shape = triangle];\n";
    ss << "    " << sst << ";\n";

    if (!acceptState.empty()) {
        ss << "    node [shape = doublecircle];\n";
        for (int p : acceptState) {
            ss << "    " << p << ";\n";
        }
    }

    if (!openGroupsState.empty()) {
        ss << "    node [shape = egg];\n";
        for (int p : openGroupsState) {
            ss << "    " << p << ";\n";
            std::cout << p << std::endl;
        }
    }
    if (!closeGroupsState.empty()) {
        ss << "    node [shape = egg];\n";
        for (int p : closeGroupsState) {
            ss << "    " << p << ";\n";
            std::cout << p << std::endl;
        }
    }
    ss << "    node [shape = circle];\n";

    for (const auto & p : transition) {
        int cs = p.first.first;
        char c = p.first.second;

        ss << "    " << cs << " -> " << p.second <<
            " [label = \"" << c << "\"];\n";
    }

    ss << "}\n";
}