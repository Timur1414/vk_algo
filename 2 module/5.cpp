#include "5.h"

#include <iostream>
#include <queue>
#include <map>

std::map<byte, std::string> codes;

class Node {
private:
    byte key;
    int frequency;
    Node* left;
    Node* right;
public:
    Node() {
        key = 0;
        frequency = 0;
        left = nullptr;
        right = nullptr;
    }
    ~Node() {
        delete left;
        delete right;
    }
    Node(byte key) {
        this->key = key;
        frequency = 0;
        left = nullptr;
        right = nullptr;
    }
    Node(byte key, int frequency) {
        this->key = key;
        this->frequency = frequency;
        left = nullptr;
        right = nullptr;
    }
    Node(const Node& node) {
        this->key = node.key;
        this->frequency = node.frequency;
        this->left = node.left;
        this->right = node.right;
    }
    Node(Node&& node) {
        this->key = node.key;
        this->frequency = node.frequency;
        this->left = node.left;
        this->right = node.right;
        node.key = 0;
        node.frequency = 0;
        node.left = nullptr;
        node.right = nullptr;
    }
    Node& operator=(const Node& node) {
        this->key = node.key;
        this->frequency = node.frequency;
        this->left = node.left;
        this->right = node.right;
        return *this;
    }
    Node& operator=(Node&& node) {
        this->key = node.key;
        this->frequency = node.frequency;
        this->left = node.left;
        this->right = node.right;
        node.key = 0;
        node.frequency = 0;
        node.left = nullptr;
        node.right = nullptr;
        return *this;
    }

    int get_frequency() const {
        return frequency;
    }
    void set_left(Node* node) {
        left = node;
    }
    void set_right(Node* node) {
        right = node;
    }
    Node* get_left() const {
        return left;
    }
    Node* get_right() const {
        return right;
    }
    byte get_key() const {
        return key;
    }
};

class Comparator {
public:
    bool operator()(Node* a, Node* b) const {
        return a->get_frequency() > b->get_frequency();
    }
};

void generate_codes(Node* root, std::string str, std::map<byte, std::string>& code_map) {
    if (root == nullptr)
        return;
    if (!root->get_right() && !root->get_left()) {
        code_map[root->get_key()] = str;
    }
    generate_codes(root->get_left(), str + "0", code_map);
    generate_codes(root->get_right(), str + "1", code_map);
}

void create_huffman_map(const std::vector<byte>& bytes) {
    std::map<byte, int> map;
    for (byte i : bytes)
        map[i]++;
    std::priority_queue<Node*, std::vector<Node*>, Comparator> queue;
    for (std::pair<byte, int> item : map) {
        Node* new_node = new Node(item.first, item.second);
        queue.push(new_node);
    }
    while (queue.size() > 1) {
        Node* first = queue.top();
        queue.pop();
        Node* second = queue.top();
        queue.pop();
        int sum_frequency = first->get_frequency() + second->get_frequency();
        Node* new_node = new Node(' ', sum_frequency);
        new_node->set_left(first);
        new_node->set_right(second);
        queue.push(new_node);
    }
    Node* root = queue.top();
    queue.pop();
    std::map<byte, std::string> code_map;
    generate_codes(root, "", code_map);
    codes = code_map;
    delete root;  // оставить дерево; кодирование и декодирование по бин дереву
}


void Encode(IInputStream& original, IOutputStream& compressed) {
    std::vector<byte> bytes;
    byte tmp;
    while (original.Read(tmp))
        bytes.push_back(tmp);
    create_huffman_map(bytes);
    for (byte i : bytes) {
        std::string encoded = codes[i];
        for (byte j : encoded) {
            compressed.Write(j);
        }
    }
}

bool is_code_correct(const std::string& code) {
    for (auto item : codes)
        if (item.second == code)
            return true;
    return false;
}
byte find_decoded_byte(const std::string& code) {
    for (auto item : codes) {
        if (item.second == code)
            return item.first;
    }
    return 0;
}

void Decode(IInputStream& compressed, IOutputStream& original) {
    // for (auto item : codes) {
    //     std::cout << int(item.first) << ": " << item.second << std::endl;
    // }
    std::string cur_code;
    byte tmp;
    while (compressed.Read(tmp)) {
        cur_code += tmp;
        if (is_code_correct(cur_code)) {
            byte result = find_decoded_byte(cur_code);
            std::cout << cur_code << " -> " << int(result) << std::endl;
            original.Write(result);
            cur_code = "";
        }
    }
}
