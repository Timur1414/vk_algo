#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

template <typename T>
class Compare {
public:
    bool operator()(const T& a, const T& b) {
        return a < b;
    }
};

template <typename T, typename C>
class Tree;

template <typename T, typename C>
class Node {
private:
    std::vector<T> keys;
    std::vector<Node*> children;
    bool is_leaf;

    friend class Tree<T, C>;
public:
    Node() {
        is_leaf = true;
    }
    ~Node() {
        for (Node* child : children)
            delete child;
    }
    Node(const Node& node) {
        keys = node.keys;
        children = node.children;
        is_leaf = node.is_leaf;
    }
    Node(Node&& node) {
        keys = std::move(node.keys);
        children = std::move(node.children);
        is_leaf = node.is_leaf;
        node.is_leaf = false;
    }
    Node& operator=(const Node& node) {
        keys = node.keys;
        children = node.children;
        is_leaf = node.is_leaf;
        return *this;
    }
    Node& operator=(Node&& node) {
        keys = std::move(node.keys);
        children = std::move(node.children);
        is_leaf = node.is_leaf;
        node.is_leaf = false;
        return *this;
    }
    void clear() {
        keys.clear();
        children.clear();
    }
};

template <typename T, typename C>
class Tree {
private:
    Node<T, C>* root;
    int t;
    C compare;

    void split_child(Node<T, C>* node, int pos) {
        Node<T, C>* child = node->children[pos];
        int mid = t - 1;
        T mid_key = child->keys[mid];
        Node<T, C>* right_child = new Node<T, C>;
        Node<T, C>* left_child = new Node<T, C>;
        right_child->is_leaf = child->is_leaf;
        left_child->is_leaf = child->is_leaf;
        right_child->keys.resize(mid);
        left_child->keys.resize(mid);
        for (int i = 0; i < 2 * t - 1; i++) {
            if (i < mid)
                left_child->keys[i] = child->keys[i];
            else if (i > mid)
                right_child->keys[i - mid - 1] = child->keys[i];
        }
        for (int i = 0; i < child->children.size(); i++) {
            if (i < t)
                left_child->children.push_back(child->children[i]);
            else
                right_child->children.push_back(child->children[i]);
        }
        auto it = remove(child->keys.begin(), child->keys.end(), mid_key);
        child->keys.erase(it, child->keys.end());
        node->keys.resize(node->keys.size() + 1);
        int pos2 = node->keys.size() - 2;
        while (pos2 >= 0 && compare(mid_key, node->keys[pos2])) {
            node->keys[pos2 + 1] = node->keys[pos2];
            pos2--;
        }
        pos2++;
        node->keys[pos2] = mid_key;
        node->children.resize(node->children.size() + 1);
        for (int i = node->children.size() - 2; i > pos; i--)
            node->children[i + 1] = node->children[i];
        node->children[pos] = left_child;
        node->children[pos + 1] = right_child;
        child->clear();
        delete child;
    }

    bool is_node_full(Node<T, C>* node) {
        return node->keys.size() == 2 * t - 1;
    }

    void recursive_add(Node<T, C>* node, const T& key) {
        if (node->is_leaf) {
            node->keys.resize(node->keys.size() + 1);
            int pos = node->keys.size() - 2;
            while (pos >= 0 && compare(key, node->keys[pos])) {
                node->keys[pos + 1] = node->keys[pos];
                pos--;
            }
            pos++;
            node->keys[pos] = key;
        }
        else {
            int pos = node->keys.size() - 1;
            while (pos >= 0 && compare(key, node->keys[pos]))
                pos--;
            pos++;
            if (is_node_full(node->children[pos])) {
                split_child(node, pos);
                if (!compare(key, node->keys[pos]))
                    pos++;
            }
            recursive_add(node->children[pos], key);
        }
    }
public:
    Tree(int t, const C& compare) {
        this->t = t;
        this->compare = compare;
        root = nullptr;
    }
    ~Tree() {
        delete root;
    }

    void add(const T& key) {
        if (root == nullptr)
            root = new Node<T, C>;
        if (is_node_full(root)) {
            Node<T, C>* new_root = new Node<T, C>;
            new_root->is_leaf = false;
            new_root->children.push_back(root);
            root = new_root;
            split_child(root, 0);
        }
        recursive_add(root, key);
    }
    void show(std::ostream& out) {
        std::queue<std::pair<Node<T, C>*, int>> queue;
        queue.push({root, 0});
        int last_layer = 0;
        while (!queue.empty()) {
            Node<T, C>* node = queue.front().first;
            int cur_layer = queue.front().second;
            queue.pop();
            if (cur_layer != last_layer) {
                out << std::endl;
                last_layer = cur_layer;
            }
            for (const T& key : node->keys) {
                out << key << " ";
            }
            for (Node<T, C>* child : node->children) {
                queue.push({child, cur_layer + 1});
            }
        }
    }
};


int main() {
    // В-дерево.
    Compare<int> compare;
    int t = 0;
    std::cin >> t;
    Tree<int, Compare<int>> tree(t, compare);
    int key;
    while (std::cin >> key)
        tree.add(key);
    tree.show(std::cout);

    return 0;
}