#include <iostream>
#include <string>
#include <vector>


class StringHasher {
private:
    unsigned p;
public:
    StringHasher() {
        p = 1;
    }
    StringHasher(unsigned p) {
        this->p = p;
    }
    unsigned operator()(const std::string& key) const {
        unsigned hash = 0;
        for (const char& c : key)
            hash = hash * p + c;
        return hash;
    }
    unsigned odd_hash(const std::string& key) const {
        unsigned hash = this->operator()(key);
        return 2 * hash + 1;
    }
};

enum State {
    empty,
    locked,
    deleted,
};

template<typename T, typename H>
class HashTable;

template<typename T, typename H>
class TableItem {
private:
    T key;
    unsigned hash;
    int state;

    friend class HashTable<T, H>;
public:
    TableItem() {
        hash = 0;
        state = empty;
    }
    TableItem(const TableItem& oth) {
        key = oth.key;
        hash = oth.hash;
        state = oth.state;
    }
    TableItem(TableItem&& oth) {
        key = oth.key;
        hash = oth.hash;
        state = oth.state;
        oth.key.clear();
        oth.hash = 0;
        oth.state = empty;
    }
    TableItem& operator=(const TableItem& oth) {
        key = oth.key;
        hash = oth.hash;
        state = oth.state;
        return *this;
    }
    TableItem& operator=(TableItem&& oth) {
        key = oth.key;
        hash = oth.hash;
        state = oth.state;
        oth.key.clear();
        oth.hash = 0;
        oth.state = empty;
        return *this;
    }

    void set_key(const T& key, unsigned hash) {
        this->key = key;
        this->hash = hash;
        state = locked;
    }
    void clear_key() {
        this->key.clear();
        this->hash = 0;
        this->state = deleted;
    }
};

template<typename T, typename H>
class HashTable {
private:
    int count;
    int locked_count;
    std::vector<TableItem<T, H>> arr;
    const int INIT_SIZE = 8;
    H hasher1;
    H hasher2;

    void resize_arr() {
        std::vector<TableItem<T, H>> old_arr(std::move(arr));
        if (locked_count * 4 >= old_arr.size() * 3)
            arr.resize(old_arr.capacity() * 2);
        else
            arr.resize(old_arr.capacity());
        count = 0;
        locked_count = 0;
        for (int i = 0; i < old_arr.size(); i++)
            if (old_arr[i].state == locked) {
                add_key(old_arr[i].key, old_arr[i].hash);
            }
    }
public:
    HashTable(const H& hasher1, const H& hasher2) {
        arr.resize(INIT_SIZE);
        this->hasher1 = hasher1;
        this->hasher2 = hasher2;
        count = 0;
        locked_count = 0;
    }

    bool in(const T& key) const {
        unsigned hash = hasher1(key);
        unsigned index = hash % arr.capacity();
        unsigned prob_hash = hasher2.odd_hash(key);
        if (prob_hash == 0)
            prob_hash = 1;
        int i = 0;
        while (i < arr.capacity() && arr[index].state != empty) {
            if (arr[index].state == locked && arr[index].key == key)
                return true;
            i++;
            index = (hash + i * prob_hash) % arr.capacity();
        }
        return false;
    }
    bool add_key(const T& key, int _hash = -1) {
        if ((count + 1) * 4 >= arr.size() * 3)
            resize_arr();
        unsigned hash = 0;
        if (_hash == -1)
            hash = hasher1(key);
        else
            hash = _hash;
        unsigned index = hash % arr.capacity();
        unsigned first_deleted = -1;
        unsigned prob_hash = hasher2.odd_hash(key);
        if (prob_hash == 0)
            prob_hash = 1;
        int i = 0;
        while (i < arr.capacity() && arr[index].state != empty) {
            if (arr[index].state == deleted && first_deleted == -1)
                first_deleted = index;
            if (arr[index].state == locked && arr[index].key == key)
                return false;
            i++;
            index = (hash + i * prob_hash) % arr.capacity();
        }
        if (first_deleted != -1)
            arr[first_deleted].set_key(key, hash);
        else
            arr[index].set_key(key, hash);
        count++;
        locked_count++;
        return true;
    }
    bool delete_key(const T& key) {
        unsigned hash = hasher1(key);
        unsigned index = hash % arr.capacity();
        unsigned prob_hash = hasher2.odd_hash(key);
        if (prob_hash == 0)
            prob_hash = 1;
        int i = 0;
        while (i < arr.capacity() && arr[index].state != empty) {
            if (arr[index].state == locked && arr[index].key == key) {
                arr[index].clear_key();
                locked_count--;
                return true;
            }
            i++;
            index = (hash + i * prob_hash) % arr.capacity();
        }
        return false;
    }
};


int main() {
    // 1.2 Хеш-таблица с пробированием в виде двойного хеширования.
    StringHasher hasher(71);
    StringHasher additional_hasher(137);
    HashTable<std::string, StringHasher> table(hasher, additional_hasher);
    char cmd = 0;
    std::string key;
    while (std::cin >> cmd >> key) {
        switch (cmd) {
            case '+':
                std::cout << (table.add_key(key) ? "OK\n" : "FAIL\n");
                break;
            case '-':
                std::cout << (table.delete_key(key) ? "OK\n" : "FAIL\n");
                break;
            case '?':
                std::cout << (table.in(key) ? "OK\n" : "FAIL\n");
                break;
            default: break;
        }
    }

    return 0;
}
