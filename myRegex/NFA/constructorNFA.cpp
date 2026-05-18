#include "constructorNFA.h"

#include <memory_resource>


std::unique_ptr<NFA> ConstructorNFA::createNFA(std::string s) {
    parser->pars(s);

   std::unique_ptr<NFA> res = std::move(recursiveMak(parser->root));
    return res;
}


std::unique_ptr<NFA>ConstructorNFA::recursiveMak(std::unique_ptr<NNode> &node) {
    if (node == nullptr) return nullptr;
    std::unique_ptr<NFA> nfaLeft = std::move(recursiveMak(node->_left));
    std::unique_ptr<NFA> nfaRight = std::move(recursiveMak(node->_right));
    recursiveMak(node->_right);
    switch (node->type) {
        case NNType::A: {
            int start  = vertexCounter++;
            int end    = vertexCounter++;
            TM loc;
            loc.insert({{start, node->_data}, end});
            std::set<int> allStatesloc ={start, end};
            std::set<int> locOr;
            return std::make_unique<NFA>(start, end, allStatesloc, loc, std::map<int,int>(), std::map<int,int>(), parser->alphabet, locOr, std::map<int,int>());
        }break;

        case NNType::Eps: {
            int start  = vertexCounter++;
            int end    = vertexCounter++;
            TM loc;
            std::set<int> allStatesloc ={start, end};
            loc.insert({{start, '$'}, end});
            std::set<int> locOr;
            return std::make_unique<NFA>(start, end, allStatesloc, loc, std::map<int,int>(), std::map<int,int>(), parser->alphabet, locOr, std::map<int,int>());
        }break;
        case NNType::OR: {
            if (nfaRight == nullptr || nfaRight == nullptr) throw std::invalid_argument("NFA is null in OR proc");
            int start = vertexCounter++;
            int end    = vertexCounter++;
            TM loc;
            loc.insert(nfaLeft->transitionMap.begin(), nfaLeft->transitionMap.end());
            loc.insert(nfaRight->transitionMap.begin(), nfaRight->transitionMap.end());
            loc.insert({{start, '$'}, nfaLeft->startState});
            loc.insert({{start, '$'}, nfaRight->startState});
            loc.insert({{nfaLeft->endStates, '$'}, end});
            loc.insert({{nfaRight->endStates, '$'}, end});
            std::set<int> allStatesloc (nfaRight->allStates.begin(), nfaRight->allStates.end());
            allStatesloc.insert(nfaLeft->allStates.begin(), nfaLeft->allStates.end());
            allStatesloc.insert(start);
            allStatesloc.insert(end);
            std::map<int, int> locOpenGS(nfaLeft->openGroupsState.begin(), nfaLeft->openGroupsState.end());
            locOpenGS.insert(nfaRight->openGroupsState.begin(), nfaRight->openGroupsState.end());
            std::map<int, int> locCloseGS(nfaLeft->closeGroupsState.begin(), nfaLeft->closeGroupsState.end());
            locCloseGS.insert(nfaRight->closeGroupsState.begin(),nfaRight->closeGroupsState.end());
            std::set<int> locOr(nfaLeft->orStates.begin(), nfaLeft->orStates.end());
            locOr.insert(nfaRight->orStates.begin(), nfaRight->orStates.end());
            locOr.insert(start);
            std::map<int, int> locRG(nfaLeft->referenceG.begin(), nfaLeft->referenceG.end());
            locRG.insert(nfaRight->referenceG.begin(), nfaRight->referenceG.end());

            return std::make_unique<NFA>(start, end, allStatesloc, loc, locOpenGS, locCloseGS, parser->alphabet, locOr, locRG);

        }break;

        case NNType::CON: {
            if (nfaRight == nullptr || nfaRight == nullptr) throw std::invalid_argument("NFA is null in CON proc");
            TM loc;
            loc.insert(nfaRight->transitionMap.begin(), nfaRight->transitionMap.end());
            loc.insert(nfaLeft->transitionMap.begin(), nfaLeft->transitionMap.end());
            loc.insert({{nfaLeft->endStates, '$'}, nfaRight->startState});
            std::set<int> allStatesloc (nfaRight->allStates.begin(), nfaRight->allStates.end());
            allStatesloc.insert(nfaLeft->allStates.begin(), nfaLeft->allStates.end());
            std::map<int, int> locOpenGS(nfaLeft->openGroupsState.begin(), nfaLeft->openGroupsState.end());
            locOpenGS.insert(nfaRight->openGroupsState.begin(), nfaRight->openGroupsState.end());
           std::map<int, int> locCloseGS(nfaLeft->closeGroupsState.begin(), nfaLeft->closeGroupsState.end());
            locCloseGS.insert(nfaRight->closeGroupsState.begin(),nfaRight->closeGroupsState.end());
            std::set<int> locOr(nfaLeft->orStates.begin(), nfaLeft->orStates.end());
            locOr.insert(nfaRight->orStates.begin(), nfaRight->orStates.end());
            std::map<int, int> locRG(nfaLeft->referenceG.begin(), nfaLeft->referenceG.end());
            locRG.insert(nfaRight->referenceG.begin(), nfaRight->referenceG.end());
            return std::make_unique<NFA>(nfaLeft->startState, nfaRight->endStates, allStatesloc,loc ,locOpenGS, locCloseGS, parser->alphabet, locOr, locRG);
        }break;

        case NNType::STAR: {
            if (nfaLeft == nullptr)throw std::invalid_argument("NFA is null in * proc");
            TM loc;
            int start = vertexCounter++;
            int end    = vertexCounter++;
            loc.insert(nfaLeft->transitionMap.begin(), nfaLeft->transitionMap.end());
            loc.insert({{nfaLeft->endStates, '$'}, nfaLeft->startState});
            loc.insert({{start, '$'}, nfaLeft->startState});
            loc.insert({{start, '$'}, end});
            loc.insert({{nfaLeft->endStates, '$'}, end});
            std::set<int> allStatesloc (nfaLeft->allStates.begin(), nfaLeft->allStates.end());
            allStatesloc.insert(start);
            allStatesloc.insert(end);
            std::map<int, int> locOGS(nfaLeft->openGroupsState.begin(), nfaLeft->openGroupsState.end());
            std::map<int, int> locCGS(nfaLeft->closeGroupsState.begin(), nfaLeft->closeGroupsState.end());
            std::set<int> locOr(nfaLeft->orStates.begin(), nfaLeft->orStates.end());
            std::map<int, int> locRG(nfaLeft->referenceG.begin(), nfaLeft->referenceG.end());
            return std::make_unique<NFA>(start, end,allStatesloc, loc,locOGS, locCGS, parser->alphabet, locOr, locRG);
        }break;
        case NNType::PLUS: {
            if (nfaLeft == nullptr)throw std::invalid_argument("NFA is null in + proc");
            TM loc;
            int start = vertexCounter++;
            int end    = vertexCounter++;
            loc.insert(nfaLeft->transitionMap.begin(), nfaLeft->transitionMap.end());
            loc.insert({{nfaLeft->endStates, '$'}, nfaLeft->startState});
            loc.insert({{start, '$'}, nfaLeft->startState});
            loc.insert({{nfaLeft->endStates, '$'}, end});
            std::set<int> allStatesloc (nfaLeft->allStates.begin(), nfaLeft->allStates.end());
            allStatesloc.insert(start);
            allStatesloc.insert(end);
            std::map<int, int> locOGS(nfaLeft->openGroupsState.begin(), nfaLeft->openGroupsState.end());
            std::map<int, int> locCGS(nfaLeft->closeGroupsState.begin(), nfaLeft->closeGroupsState.end());
            std::set<int> locOr(nfaLeft->orStates.begin(), nfaLeft->orStates.end());
            std::map<int, int> locRG(nfaLeft->referenceG.begin(), nfaLeft->referenceG.end());
            return std::make_unique<NFA>(start, end,allStatesloc, loc,locOGS, locCGS, parser->alphabet, locOr, locRG);
        }break;

        case NNType::CB: {
            if (nfaLeft == nullptr)throw std::invalid_argument("NFA is null in CON proc");
            TM loc;
            int start = vertexCounter++;
            int end    = vertexCounter++;
            loc.insert(nfaLeft->transitionMap.begin(), nfaLeft->transitionMap.end());
            loc.insert({{start, '$'}, nfaLeft->startState});
            loc.insert({{nfaLeft->endStates, '$'}, end});
            std::set<int> allStatesloc (nfaLeft->allStates.begin(), nfaLeft->allStates.end());
            std::map<int, int> locOGS(nfaLeft->openGroupsState.begin(), nfaLeft->openGroupsState.end());
            std::map<int, int> locCGS(nfaLeft->closeGroupsState.begin(), nfaLeft->closeGroupsState.end());
            locOGS.insert({start, node->groupNumb});
            locCGS.insert({end, node->groupNumb});
            allStatesloc.insert(start);
            allStatesloc.insert(end);
            std::map<int, int> locRG(nfaLeft->referenceG.begin(), nfaLeft->referenceG.end());
            std::set<int> locOr(nfaLeft->orStates.begin(), nfaLeft->orStates.end());
            return std::make_unique<NFA>(start, end,allStatesloc, loc,locOGS, locCGS, parser->alphabet, locOr, locRG);
        }break;
        case NNType::EMPTY: {
            return nfaLeft;
        }
        case NNType::NG : {
            int start  = vertexCounter++;
            int end    = start;
            std::cout << start << std::endl;
            std::map<int, int> locRG{{start, node->groupNumb}};
            TM loc;
            std::set<int> allStatesloc ={start};
            std::set<int> locOr;
            return std::make_unique<NFA>(start, end, allStatesloc, loc, std::map<int,int>(), std::map<int,int>(), parser->alphabet, locOr, locRG);
        }break;
            default: return nullptr;
    }

}

