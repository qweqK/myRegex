//
// Created by user on 15.03.2026.
//

#ifndef TEST_VISUALTREE_H
#define TEST_VISUALTREE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <memory>
#include <sstream>

// Вспомогательная функция для превращения множества {1, 2} в строку
inline std::string setToString(const std::set<int>& s) {
    std::stringstream ss;
    ss << "{";
    for (auto it = s.begin(); it != s.end(); ++it) {
        ss << *it << (std::next(it) == s.end() ? "" : ", ");
    }
    ss << "}";
    return ss.str();
}

// Экранирование символов { } | < > для формата Graphviz Record
inline std::string escapeDot(std::string s) {
    std::string result;
    for (char c : s) {
        if (c == '{' || c == '}' || c == '|' || c == '<' || c == '>' || c == '\\') {
            result += '\\'; // Добавляем бэкслеш перед служебным символом
        }
        result += c;
    }
    return result;
}

// Рекурсивный обход дерева
inline void generateDot(const Node* node, std::ostream& out) {
    if (!node) return;

    // Используем адрес узла как уникальный идентификатор
    size_t id = reinterpret_cast<size_t>(node);

    // Подготовка данных для лейбла
    std::string dataStr(1, node->_data);
    std::string firstposStr = setToString(node->_firstpos);
    std::string lastposStr = setToString(node->_lastpos);
    std::string nilStr = node->_nullable ? "nullable" : "not nullable";

    // Формируем лейбл в формате "ячеек" (record)
    // Формат: { nullable | символ | { firstpos | lastpos } }
    std::stringstream label;
    label << "{ " << escapeDot(nilStr) << " | "
          << "Data: " << escapeDot(dataStr) << " | "
          << "{ f: " << escapeDot(firstposStr) << " | l: " << escapeDot(lastposStr) << " } }";

    out << "  node" << id << " [label=\"" << label.str() << "\", shape=Mrecord";

    // Подсветка операторов для наглядности
    if (node->_data == '*' || node->_data == '|' || node->_data == '.') {
        out << ", color=\"#e67e22\", style=filled, fillcolor=\"#fff5e6\"";
    } else {
        out << ", color=\"#2ecc71\", style=filled, fillcolor=\"#f0fff4\"";
    }
    out << "];\n";

    // Связи с левым и правым сыном
    if (node->_left) {
        size_t leftId = reinterpret_cast<size_t>(node->_left.get());
        out << "  node" << id << " -> node" << leftId << ";\n";
        generateDot(node->_left.get(), out);
    }
    if (node->_right) {
        size_t rightId = reinterpret_cast<size_t>(node->_right.get());
        out << "  node" << id << " -> node" << rightId << ";\n";
        generateDot(node->_right.get(), out);
    }
}

// Главная функция для сохранения графа в файл
inline void saveGraph(const Node* root, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return;
    }

    file << "digraph SyntaxTree {\n";
    file << "  // Настройки графа\n";
    file << "  rankdir=TB;\n";
    file << "  nodesep=0.5;\n";
    file << "  ranksep=0.5;\n";
    file << "  node [fontname=\"Verdana\", fontsize=10];\n";
    file << "  edge [color=\"#34495e\", penwidth=1.2];\n";

    generateDot(root, file);

    file << "}\n";
    file.close();
    std::cout << "Successfully saved DOT file: " << filename << std::endl;
}

#endif //TEST_VISUALTREE_H