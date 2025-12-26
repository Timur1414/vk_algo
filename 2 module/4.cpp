#include <iostream>

class Compare {
public:
    bool operator()(const int& a, const int& b) const {
        return a > b;
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
    int height;
    int count;

    friend class Tree<T>;
public:
    Node() {
        key = 0;
        right = nullptr;
        left = nullptr;
        height = 1;
        count = 1;
    }
    Node(int key) {
        this->key = key;
        right = nullptr;
        left = nullptr;
        height = 1;
        count = 1;
    }
    Node(const Node& oth) {
        key = oth.key;
        right = oth.right;
        left = oth.left;
        height = oth.height;
        count = oth.count;
    }
    Node(Node&& oth) {
        key = oth.key;
        right = oth.right;
        left = oth.left;
        height = oth.height;
        count = oth.count;
        oth.key = 0;
        oth.right = nullptr;
        oth.left = nullptr;
        oth.height = 1;
        oth.count = 1;
    }
    Node& operator=(const Node& oth) {
        key = oth.key;
        right = oth.right;
        left = oth.left;
        height = oth.height;
        count = oth.count;
        return *this;
    }
    Node& operator=(Node&& oth) {
        key = oth.key;
        right = oth.right;
        left = oth.left;
        height = oth.height;
        count = oth.count;
        oth.key = 0;
        oth.right = nullptr;
        oth.left = nullptr;
        oth.height = 1;
        oth.count = 1;
        return *this;
    }
};

template <typename T>
class Tree {
private:
    Node<T>* root;
    T compare;

    void clear(Node<T>* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    int get_height(Node<T>* node) {
        return node ? node->height : 0;
    }

    int get_count(Node<T>* node) {
        return node ? node->count : 0;
    }

    void fix_height(Node<T>* node) {
        node->height = 1 + std::max(get_height(node->left), get_height(node->right));
        node->count = 1 + get_count(node->left) + get_count(node->right);
    }

    int diff_height(Node<T>* node) {
        return get_height(node->right) - get_height(node->left);
    }

    Node<T>* rotate_left(Node<T>* node) {
        Node<T>* right_child = node->right;
        node->right = right_child->left;
        right_child->left = node;
        fix_height(node);
        fix_height(right_child);
        return right_child;
    }

    Node<T>* rotate_right(Node<T>* node) {
        Node<T>* left_child = node->left;
        node->left = left_child->right;
        left_child->right = node;
        fix_height(node);
        fix_height(left_child);
        return left_child;
    }

    Node<T>* balance(Node<T>* node) {
        fix_height(node);
        if (diff_height(node) == 2) {
            if (diff_height(node->right) < 0)
                node->right = rotate_right(node->right);
            return rotate_left(node);
        }
        if (diff_height(node) == -2) {
            if (diff_height(node->left) > 0)
                node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        return node;
    }

    Node<T>* recursive_add(Node<T>* node, int key, int& pos) {
        if (!node)
            return new Node<T>(key);
        if (compare(key, node->key))
            node->left = recursive_add(node->left, key, pos);
        else {
            pos += get_count(node->left) + 1;
            node->right = recursive_add(node->right, key, pos);
        }
        return balance(node);
    }

    Node<T>* recursive_remove(Node<T>* node, int index) {
        if (!node)
            return nullptr;
        int left_count = get_count(node->left);
        if (index < left_count)
            node->left = recursive_remove(node->left, index);
        else if (index > left_count)
            node->right = recursive_remove(node->right, index - left_count - 1);
        else {
            Node<T>* left_subtree = node->left;
            Node<T>* right_subtree = node->right;
            delete node;
            if (!right_subtree)
                return left_subtree;
            Node<T>* min = nullptr;
            right_subtree = find_and_remove_min(right_subtree, min);
            min->right = right_subtree;
            min->left = left_subtree;
            return balance(min);
        }
        return balance(node);
    }

    Node<T>* find_and_remove_min(Node<T>* node, Node<T>*& min_node) {
        if (node->left == nullptr) {
            min_node = node;
            return node->right;
        }
        node->left = find_and_remove_min(node->left, min_node);
        return balance(node);
    }
public:
    Tree(const T& compare) {
        root = nullptr;
        this->compare = compare;
    }
    ~Tree() {
        clear(root);
    }

    int add(int key) {
        int position = 0;
        root = recursive_add(root, key, position);
        return position;
    }

    void remove(int index) {
        root = recursive_remove(root, index);
    }
};


int main() {
    // 4.1 Солдаты АВЛ.
    Compare compare;
    Tree<Compare> tree(compare);
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int cmd = 0, height = 0;
        std::cin >> cmd >> height;
        if (cmd == 1) {
            int position = tree.add(height);
            std::cout << position << std::endl;
        }
        else
            tree.remove(height);
    }

    return 0;
}
