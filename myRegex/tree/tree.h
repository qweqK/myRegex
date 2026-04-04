#pragma once
#include <memory>
#include <set>
#include <vector>
class Node {
public:
    enum class NodeType { A, Eps, OR, STAR, CON, PLUS};
    char _data;
    bool _nullable;
    NodeType _nodeType;
    std::set<int> _firstpos;
    std::set<int> _lastpos;

    std::unique_ptr<Node> _left;
    std::unique_ptr<Node> _right;



    Node(char data, bool nullable,NodeType t ,std::set<int> firstpos, std::set<int> lastpos) :
    _data(data), _nullable(nullable), _nodeType(t),
    _firstpos(std::move(firstpos)), _lastpos(std::move(lastpos)) {}
    Node(char data, bool nullable, NodeType t,std::set<int> firstpos, std::set<int> lastpos, std::unique_ptr<Node> left, std::unique_ptr<Node> right) :
    _data(data), _nullable(nullable), _nodeType(t),
    _firstpos(std::move(firstpos)),_lastpos(std::move(lastpos)),
    _left(std::move(left)), _right(std::move(right)) {}

    Node(const Node &other) : _data(other._data), _nullable(other._nullable), _firstpos(other._firstpos), _lastpos(other._lastpos) {

        if (other._left) _left = std::make_unique<Node>(*other._left);

        if (other._right) _right = std::make_unique<Node>(*other._right);
    }

    std::unique_ptr<Node> clone() {return std::make_unique<Node>(*this);}
};


class Tree {
    public:
    std::unique_ptr<Node> root;
};

