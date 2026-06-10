#ifndef BST_H
#define BST_H

#include <iostream>
#include <functional>

class BST
{
public:
    class Node;

    BST();
    BST(const BST& bst);
    BST& operator=(const BST& bst);
    BST(BST&& bst) noexcept;
    BST& operator=(BST&& bst) noexcept;
    BST(std::initializer_list<int>);

    Node*& get_root() const;
    void bfs(std::function<void(Node*& node)> func);
    size_t length() const;
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);

    ~BST();

private:
    Node* root;
};

class BST::Node
{
public:
	Node(int value, Node* left, Node* right);
	Node();
	Node(const Node& node);

	int value;
	Node* left;
	Node* right;
};

std::ostream& operator<<(std::ostream& os, const BST::Node& node);
std::ostream& operator<<(std::ostream& os, const BST& bst);

bool operator==(const BST::Node& node, const int& a);
bool operator==(const int& a, const BST::Node& node);

bool operator<(const int& a, const BST::Node& node);
bool operator<(const BST::Node& node, const int& a);

bool operator<=(const int& a, const BST::Node& node);
bool operator<=(const BST::Node& node, const int& a);

bool operator>(const int& a, const BST::Node& node);
bool operator>(const BST::Node& node, const int& a);

bool operator>=(const int& a, const BST::Node& node);
bool operator>=(const BST::Node& node, const int& a);

BST& operator++(BST& bst);
BST operator++(BST& bst, int);

#endif //BST_H