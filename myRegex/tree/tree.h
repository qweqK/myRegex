#pragma once
#include <memory>
#include <set>
#include <vector>
class Node {
public:
    char _data;
    bool _nullable;

    std::set<int> _firstpos;
    std::set<int> _lastpos;

    std::unique_ptr<Node> _left;
    std::unique_ptr<Node> _right;



    Node(char data, bool nullable, std::set<int> firstpos, std::set<int> lastpos) :
    _data(data), _nullable(nullable),
    _firstpos(std::move(firstpos)), _lastpos(std::move(lastpos)) {}
    Node(char data, bool nullable, std::set<int> firstpos, std::set<int> lastpos, std::unique_ptr<Node> left, std::unique_ptr<Node> right) :
    _data(data), _nullable(nullable),
    _firstpos(std::move(firstpos)),_lastpos(std::move(lastpos)),
    _left(std::move(left)), _right(std::move(right)) {}
};


class Tree {
    public:
    std::unique_ptr<Node> root;
};

