#pragma once
#include <memory>
#include "parsInNFA.h"
#include "NFA.h"


class ConstructorNFA {
    std::unique_ptr<parsInNFA> parser;
    using TM =  std::multimap<std::pair<int, char>, int>;
    std::map<int, int> capVert;
    int vertexCounter = 0;
    public:
    ConstructorNFA() : parser(std::make_unique<parsInNFA>()) {}
    std::unique_ptr<NFA> createNFA(std::string);
   std::unique_ptr<NFA>recursiveMak(std::unique_ptr<NNode> & node);

};
