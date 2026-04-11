
#pragma once
#include <map>
#include <set>

// class MultiDFA {
//     std::map<std::pair<int, char>, int> newTransitions;
//     std::set<int>   acceptState;
//
//     std::set<std::pair<int, int>> mAllState;
//     std::pair<int, int> mStart;
// public:
//     MultiDFA(std::map<std::pair<std::pair<int, int>, char>, std::pair<int, int>> &mTransitions, std::set<std::pair<int,int>> &mAllT, std::pair<int, int> &mStart) :
//     mTransitions(std::move(mTransitions)), mAllState(std::move(mAllT)), mStart(std::move(mStart)){}
//
//
//
//     std::map<std::pair<std::pair<int, int>, char>, std::pair<int, int>> &getMTM() {return mTransitions;}
//     std::set<std::pair<int, int>> &getMAllState() {return mAllState;}
//     std::pair<int, int> &getMStart() {return mStart;}
// };


class MultiDFA {
    std::map<std::pair<int, char>, int> mTransitions;
    std::map<std::pair<int, int>, int> mAllState;
    std::set<char> alphabet;
    int mStart;

public:
    MultiDFA(std::map<std::pair<int, char>, int> &mTransitions, std::map<std::pair<int, int>, int> &mAllT, int start, std::set<char> &alphabet) :
    mTransitions(std::move(mTransitions)), mAllState(std::move(mAllT)), mStart(start), alphabet(std::move(alphabet)){}

    std::map<std::pair<int, char>, int> &getMTM() {return mTransitions;}
    std::map<std::pair<int, int>, int> &getMAllState() {return mAllState;}
    int getMStart() {return mStart;}
    std::set<char> &getAlphabet() {return alphabet;}
};