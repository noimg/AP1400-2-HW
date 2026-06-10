#include "bst.h"

#include <iomanip>
#include <vector>
#include <queue>

BST::Node::Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}

BST::Node::Node() : Node(0, nullptr, nullptr) {}

BST::Node::Node(const Node& node) : Node(node.value, node.left, node.right) {}

std::ostream& operator<<(std::ostream& os, const BST::Node& node)
{
    os << "node: " << &node << "\nvalue: " << node.value << "\nleft: " << node.left << "\nright: " << node.right << "\n";
    return os;
}

bool operator==(const BST::Node& node, const int& num) { return node.value == num; }
bool operator==(const int& num, const BST::Node& node) { return num == node.value; }

bool operator<(const int& num, const BST::Node& node) { return num < node.value; }
bool operator<(const BST::Node& node, const int& num) { return node.value < num; }

bool operator<=(const int& num, const BST::Node& node) { return num <= node.value; }
bool operator<=(const BST::Node& node, const int& num) { return node.value <= num; }

bool operator>(const int& num, const BST::Node& node) { return num > node.value; }
bool operator>(const BST::Node& node, const int& num) { return node.value > num; }

bool operator>=(const int& num, const BST::Node& node) { return num >= node.value; }
bool operator>=(const BST::Node& node, const int& num) { return node.value >= num; }


BST::BST() : root(new Node(0, nullptr, nullptr)) {}

static void copy_BST(BST::Node* src, BST::Node*& dst)
{
	if (src)
    {
		dst = new BST::Node(src->value, 0, 0);
		copy_BST(src->left, dst->left);
		copy_BST(src->right, dst->right);
	}
}

BST::BST(const BST& bst)
{
	root = new Node(bst.root->value, nullptr, nullptr);
	if (bst.get_root())
		copy_BST(bst.get_root(), get_root());
}

BST& BST::operator=(const BST& bst)
{
	auto bst2 = new BST(bst);
	this->~BST();
	root = bst2->root;
	return *this;
}

BST::BST(BST&& bst) noexcept
{
	root = new Node(bst.root->value, 0, 0);
    root->left = bst.root->left;
	bst.root->left = nullptr;
}

BST& BST::operator=(BST&& bst) noexcept
{
	if (this != &bst)
    {
		this->~BST();
		root = new Node(bst.root->value, 0, 0);
		root->left = bst.root->left;
		bst.root->left = nullptr;
	}
	return *this;
}

BST::BST(std::initializer_list<int> ls)
{
    root = new Node(0, nullptr, nullptr);
    for (auto i : ls)
        add_node(i);
}

BST::Node*& BST::get_root() const
{
    return root->left;
}

void BST::bfs(std::function<void(Node*& node)> func)
{
    if(get_root() == nullptr)
        return;
    std::queue<Node*> q;
    q.push(get_root());
    while (!q.empty()) {
        auto pn = q.front();
        q.pop();
        func(pn);
        if (pn->left)
            q.push(pn->left);
        if (pn->right)
            q.push(pn->right);
    }
}

size_t BST::length() const
{
    return root->value;
}

bool BST::add_node(int value)
{
    Node** r = &(root->left);
    while (*r)
    {
        if ((*r)->value == value)
            return false;
        r = (value < (*r)->value) ? &((*r)->left) : &((*r)->right);
    }

    *r = new Node(value, nullptr, nullptr);
    root->value++;
    return true;
}

BST::Node** BST::find_node(int value)
{
    Node** r = &(root->left);

    while(*r)
    {
        if ((*r)->value == value)
            return r;
        else if (value < (*r)->value)
            r = &((*r)->left);
        else
            r = &((*r)->right);
    }
    return nullptr;
}

BST::Node** BST::find_parrent(int value)
{
    Node** r = &(root->left);

    while((*r)->left || (*r)->right)
    {
        if (((*r)->left && (*r)->left->value == value) || ((*r)->right && (*r)->right->value == value))
            return r;
        else if (value < (*r)->value)
            r = &((*r)->left);
        else
            r = &((*r)->right);
    }
    return nullptr;
}

static BST::Node** subtree_last(BST::Node** r)
{
    if ((*r)->right)
        return subtree_last(&((*r)->right));
    else
        return r;
}

// Actually find_predecessor
BST::Node** BST::find_successor(int value)
{
    Node** r = find_node(value);
    if ((*r)->left)
        return subtree_last(&((*r)->left));

    Node** parent = find_parrent((*r)->value);
    while (parent != nullptr && (*parent)->left == *r)
    {
        r = parent;
        parent = find_parrent((*r)->value);
    }
    return parent;
}

bool BST::delete_node(int value)
{
    Node** node = find_node(value);

    if (node == nullptr || *node == nullptr)
        return false;

    Node* target = *node;
    if (target->left == nullptr)
    {
        *node = target->right;
        delete target;
    }
    else if (target->right == nullptr)
    {
        *node = target->left;
        delete target;
    }
    else
    {
        auto pred = subtree_last(&(target->left));
        target->value = (*pred)->value;

        Node* to_delete = *pred;
        *pred = (*pred)->left;
        delete to_delete;
    }

    root->value--;
    return true;
}

BST::~BST()
{
	std::vector<Node*> nodes;
	bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
	for (auto& node : nodes)
		delete node;
}

std::ostream& operator<<(std::ostream& os, const BST& bst)
{
	std::cout << std::string(20, '*') << std::endl;
	std::queue<BST::Node*> q;
	q.push(bst.get_root());

	while (!q.empty())
    {
		auto node = q.front();
		q.pop();
		std::cout << *node << std::endl;
		if (node->left)
			q.push(node->left);
		if (node->right)
			q.push(node->right);
	}
	std::cout << std::string(20, '*') << std::endl;
	return os;
}

BST& operator++(BST& bst)
{
	bst.bfs([](BST::Node*& node) { ++node->value; });
	return bst;
}

BST operator++(BST& bst, int)
{
	BST b(bst);
	++bst;
	return b;
}
