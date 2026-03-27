#include "DFAconstruct.h"

#include <iostream>

void DFAConstructor::constructTree(std::string &str) {
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
        if (acceptState.contains(s.first.first)) {std::cout << " true"<< std::endl;}
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


void DFAMinimization::minimization() {
    std::set<int> notAcept;
    std::set_difference(AllStates.begin(), AllStates.end(), AcceptState.begin(), AcceptState.end(), std::inserter(notAcept, notAcept.end()));
    partition.push_back(AcceptState);
    partition.push_back(notAcept);
    size_t lastSize=partition.size();
     while (true) {
         for (auto & p : partition) {
            divisionGroup(p);
        }
        if (newPartitions.size() == partition.size()) break;
        partition = std::move(newPartitions);
         newPartitions.clear();
    }
    std::vector<int> groupf;

    int GI=0;
    for (auto &g : partition) {
        int s = *g.begin();
        groupf.push_back(s);
        for (auto p : g) {
            stateToGroup[p]= GI;
        }
        if (AcceptState.contains(s)) {
            newAcceptState.insert(GI);
        }
        GI++;
    }

    for (int i=0 ; i < GI; i++) {
        int s = groupf[i];
        for (auto a : alphabet) {
            newTableDFA[{i,a}] = stateToGroup[tableDFA[{s,a}]];
        }
    }



    for (auto & s :  newTableDFA) {
        std::cout << s.first.first << ": " << s.first.second << "-> "<< s.second;
        if (newAcceptState.contains(s.first.first)) {std::cout << " true"<< std::endl;}
        else {std::cout << " false"<<std::endl;}
    }




    for (int i = 0; i < newPartitions.size(); i++) {
        std::cout << i << " {";
        for (auto g: partition[i]) std::cout << g << ",";
        std::cout << "}" << std::endl;
    }

}

void DFAMinimization::divisionGroup(std::set<int> &G) {
    std::map<int, std::vector<int>> posToGroup;
    std::map<std::vector<int>, std::set<int>> f;
    for (auto a: alphabet) {
        for (auto p: G) {
            posToGroup[p].push_back(getGroupIndex(p, a));
        }
    }
    //  for (auto p: posToGroup) {
    //      std::cout << p.first << " [";
    //      for (auto a: p.second) {
    //          std::cout << a << ",";
    //      }
    //      std::cout << "]" << std::endl;
    //
    // }
    for (auto &p: posToGroup) {
        f[p.second].insert(p.first);
    }
    for (auto &a: f) {
        newPartitions.push_back(a.second);
    }
}


int DFAMinimization::getGroupIndex(int pos, char a) {
    for (int i = 0; i < partition.size(); i++) {
        if (partition[i].contains(tableDFA[{pos, a}])) {return i;}
    }
    throw std::invalid_argument("Group index out of range");
}
