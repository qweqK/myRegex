#include "DFAconstruct.h"

#include <iostream>

void DFAConstructor::constructTree(const std::string &str) {
    d->pars(str);
}


void DFAConstructor::buildDFA(std::string str) {
    str.append(".#");
    d->pars(str);
    int dontMarkIndex=0;
    Dstates.push_back(d->t.root->_firstpos);
   // NormalStates.push_back(buildNormalState());
    AllStates.insert(dontMarkIndex);
    fpTS[d->t.root->_firstpos] = 0;
    while (dontMarkIndex < Dstates.size()) {
       int currentIndex=dontMarkIndex++;
        for (auto a : d->alphabet) {
            auto set = Dstates[currentIndex];
            std::set<int>uni = getUnion(set, a);
            if (fpTS.find(uni) == fpTS.end()) {
                Dstates.push_back(uni);
                //NormalStates.push_back(buildNormalState());
                fpTS[uni] = Dstates.size() - 1;
                if (uni.contains(d->counterPos-1)) acceptState.insert(fpTS[uni]);
                AllStates.insert(fpTS[uni]);
            }
            tableDFA[std::pair<int, char>{fpTS[set], a}] = fpTS[uni];

        }
    }
}

// State DFAConstructor::buildState(std::set<int> &t) {
//     std::string s=std::to_string(Dstates.size());
//     return State{std::move(s), t, static_cast<int>(Dstates.size())};
// }

/*std::unique_ptr<NormalState> DFAConstructor::buildNormalState() {
    return std::make_unique<NormalState>(Dstates.size()-1, Dstates[Dstates.size() - 1].contains(d->counterPos-1));
}*/


std::set<int> DFAConstructor::getUnion(std::set<int> &s, char a) {
    std::set<int> uni;
    for (auto p : s) {
        if ( d->alphabetMap[p]== a) {
            uni.insert(d->followPos[p].begin(), d->followPos[p].end());
        }
    }
    return uni;
}

void DFAConstructor::printDFA() {
    std::cout<<"DFA construct"<<std::endl;
    for (auto & s : this->tableDFA) {
        std::cout << s.first.first << ": " << s.first.second << "-> "<< s.second;
        if (fpTS.contains(Dstates[s.first.first])) {std::cout << " true"<< std::endl;}
        else {std::cout << " false"<<std::endl;}

    }
}


void DFAConstructor::prinStates() {
    int i=0;
    for (auto & s : Dstates) {
        std::cout<< fpTS[s];
        std::cout << " : " << "{";
        for (auto p : s) {
            std::cout << p<< ",";
        }
        std::cout << "}" << std::endl;
        i++;
    }
}



void DFAConstructor::minimizationDFA() {
    std::map<std::set<int>, int> curPartition;
    std::map<std::set<int>, int> newPartition;
    std::set<int> dontAccept;
    std::set_difference(AllStates.begin(), AllStates.end(), acceptState.begin(), acceptState.end(), std::inserter(dontAccept, dontAccept.begin()) );
    curPartition.insert({dontAccept,0} );
    curPartition.insert({acceptState, 1});
    while (true) {
        for (auto& p: curPartition) {

        }
    }
}


