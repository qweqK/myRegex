#include "NFA.h"

#include <memory>


bool NFA::match(std::string t, msmatch &m) {
    std::stack<helpContainer> procStack;
    std::map<int, indexesGroup> groupMapfirst;
    for (auto p : openGroupsState) {
        groupMapfirst.emplace(p.second, indexesGroup(0, 0));
    }
    //std::map<int, indexesGroup> groupMapfirst = {{0, indexesGroup(0, 0)}};
    procStack.emplace(startState, 0, groupMapfirst);
    while (!procStack.empty()) {
        auto cur = procStack.top();
        procStack.pop();
        std::cout << "index: "<<cur.strIndx << "-";
        std::cout << "state: "<<cur.state << std::endl;
        if (referenceG.contains(cur.state)) {
            std::cout << "its ref";
            auto bounds =  cur.groupsLoc[referenceG[cur.state]];
            if (!bounds.isComplete) return false;
            auto checksub = t.substr(bounds.firstIdx, bounds.lastIdx-bounds.firstIdx);
            if (cur.strIndx + checksub.size() <= t.length()) {
                if (t.substr(cur.strIndx, checksub.size()) != checksub) continue;
                std::cout << "its normref" << t.substr(cur.strIndx, checksub.size()) << std::endl;
                cur.strIndx += checksub.size();
            }
            else continue;
        }

        if (openGroupsState.contains(cur.state)) {
            cur.groupsLoc[openGroupsState[cur.state]] = indexesGroup(cur.strIndx, -1);
        }

        if (closeGroupsState.contains(cur.state)) {
            cur.groupsLoc[closeGroupsState[cur.state]].lastIdx = cur.strIndx;
            cur.groupsLoc[closeGroupsState[cur.state]].isComplete = true;
        }

        if (cur.state == endStates && cur.strIndx == t.length()) {
            cur.groupsLoc[0].lastIdx = cur.strIndx;
            cur.groupsLoc[0].isComplete = true;
            m.fill(t, cur.groupsLoc);
            return true;
        }

        if (cur.strIndx < t.length()) {
            auto range = transitionMap.equal_range({cur.state, t[cur.strIndx]});
            for (; range.first != range.second; ++range.first) {
                procStack.emplace(range.first->second, cur.strIndx+1 , cur.groupsLoc);
            }
        }

        auto range2 = transitionMap.equal_range({cur.state, '$'});
        std::vector<int> da;
        for (; range2.first != range2.second; ++range2.first) {
            da.push_back(range2.first->second);
        }

        for (auto it = da.rbegin() ; it != da.rend() ; ++it) {
            procStack.emplace(*it, cur.strIndx, cur.groupsLoc);
        }


    }
    return false;
}



void NFA::graphGenerate(const std::string &outS) {

    std::set<int> acceptState={endStates};
    int sst = startState;
    TM transition = transitionMap;
    std::set<int> closeGroupsStateloc;
    std::set<int> openGroupsStateloc;
    std::set<int> zahlStateloc;
    for (auto p : openGroupsState) {openGroupsStateloc.insert(p.first);}
    for (auto p: closeGroupsState) {closeGroupsStateloc.insert(p.first);}
    for (auto p : referenceG) {zahlStateloc.insert(p.first);}
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

    if (!openGroupsStateloc.empty()) {
        ss << "    node [shape = egg];\n";
        for (int p : openGroupsStateloc) {
            ss << "    " << p << ";\n";
            std::cout << p << std::endl;
        }
    }
    if (!closeGroupsStateloc.empty()) {
        ss << "    node [shape = egg];\n";
        for (int p : closeGroupsStateloc) {
            ss << "    " << p << ";\n";
            std::cout << p << std::endl;
        }
    }
    if (!zahlStateloc.empty()) {
        ss << "    node [shape = triangle];\n";
        for (int p : zahlStateloc) {
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