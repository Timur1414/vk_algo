#include <iostream>
#include <stack>


class Compare {
public:
    bool operator()(const int& a, const int& b) const {
        return a < b;
    }
};


template<typename T>
class Tree;

template<typename T>
class Node {
private:
    int key;
    Node* right;
    Node* left;
    Node* parent;
    bool visited;

    friend class Tree<T>;
public:
    Node() {
        key = 0;
        right = nullptr;
        left = nullptr;
        parent = nullptr;
        visited = false;
    }
    Node(int key) {
        this->key = key;
        right = nullptr;
        left = nullptr;
        parent = nullptr;
        visited = false;
    }
    Node(const Node& oth) {
        key = oth.key;
        right = oth.right;
        left = oth.left;
        parent = oth.parent;
        visited = oth.visited;
    }
    Node(Node&& oth) {
        key = oth.key;
        right = oth.right;
        left = oth.left;
        parent = oth.parent;
        visited = oth.visited;
        oth.key = 0;
        oth.right = nullptr;
        oth.left = nullptr;
        oth.parent = nullptr;
        oth.visited = false;
    }
    Node& operator=(const Node& oth) {
        key = oth.key;
        right = oth.right;
        left = oth.left;
        parent = oth.parent;
        visited = oth.visited;
        return *this;
    }
    Node& operator=(Node&& oth) {
        key = oth.key;
        right = oth.right;
        left = oth.left;
        parent = oth.parent;
        visited = oth.visited;
        oth.key = 0;
        oth.right = nullptr;
        oth.left = nullptr;
        oth.parent = nullptr;
        oth.visited = false;
        return *this;
    }
};

template<typename T>
class Tree {
private:
    Node<T>* root;
    Node<T>* cur;
    Node<T>* prev;
    T compare;
    int count;
public:
    Tree(const T& compare) {
        root = nullptr;
        cur = nullptr;
        prev = nullptr;
        this->compare = compare;
        count = 0;
    }
    ~Tree() {
        cur = root;
        prev = root;
        while (cur) {
            if (cur->left)
                cur = cur->left;
            else if (cur->right)
                cur = cur->right;
            else {
                prev = cur;
                cur = cur->parent;
                if (cur) {
                    if (cur->right == prev)
                        cur->right = nullptr;
                    else
                        cur->left = nullptr;
                }
                delete prev;
            }
        }
    }

    void add(int key) {
        Node<T>* new_node = new Node<T>(key);
        if (root == nullptr) {
            root = new_node;
            return;
        }
        cur = root;
        prev = root;
        while (cur) {
            prev = cur;
            if (compare(key, cur->key))
                cur = cur->left;
            else
                cur = cur->right;
        }
        if (compare(key, prev->key))
            prev->left = new_node;
        else
            prev->right = new_node;
        new_node->parent = prev;
        count++;
    }
    void in_order_show(std::ostream& out) {
        if (root == nullptr)
            return;
        std::stack<Node<T>*> stack;
        stack.push(root);
        while (!stack.empty()) {
            Node<T>* node = stack.top();
            if (node->left && !node->left->visited)
                stack.push(node->left);
            else {
                out << node->key << " ";
                stack.pop();
                node->visited = true;
                if (node->right)
                    stack.push(node->right);
            }
        }
    }
};


int main() {
    // 2.1 Бинарное дерево с обходом in-order.
    Compare compare;
    Tree<Compare> tree(compare);
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int item = 0;
        std::cin >> item;
        tree.add(item);
    }
    tree.in_order_show(std::cout);

    return 0;
}
