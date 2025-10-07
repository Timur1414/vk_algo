#include <iostream>

using namespace std;

bool operator>(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second > b.second;
}

template <typename T>
class Heap {
private:
    T* arr;
    int size;
    int capacity;
public:
    Heap() {
        size = 0;
        capacity = 1;
        arr = new T[capacity];
    }
    ~Heap() {
        delete[] arr;
    }

    Heap(const Heap&) = delete;
    Heap(Heap&&) = delete;

    Heap& operator=(const Heap&) = delete;
    Heap& operator=(Heap&&) = delete;

    void sift_up(int index) {
        while (index > 0 && arr[index] > arr[(index - 1) / 2]) {
            swap(arr[index], arr[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void sift_down(int index) {
        while (2 * index + 1 < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int max_child = left;
            if (right < size && arr[right] > arr[left])
                max_child = right;
            if (arr[index] > arr[max_child])
                return;
            swap(arr[max_child], arr[index]);
            index = max_child;
        }
    }

    void add(T item) {
        if (size + 1 == capacity) {
            capacity *= 2;
            T* new_arr = new T[capacity];
            for (int i = 0; i < size; i++)
                new_arr[i] = arr[i];
            delete[] arr;
            arr = new_arr;
        }
        arr[size++] = item;
        sift_up(size - 1);
    }

    T get_max() {
        return arr[0];
    }

    T extract_max() {
        T res = arr[0];
        arr[0] = arr[--size];
        sift_down(0);
        return res;
    }
};

void read_users(Heap<pair<int, int>>& heap, int n) {
    for (int i = 0; i < n; i++) {
        int id = 0, frequency = 0;
        cin >> id >> frequency;
        pair<int, int> user = make_pair(id, frequency);
        heap.add(user);
    }
}

void show_first_users(Heap<pair<int, int>>& heap, int k) {
    int* ids = new int[k];
    for (int i = 0; i < k; i++) {
        pair<int, int> user = heap.extract_max();
        ids[i] = user.first;
    }
    for (int i = k - 1; i >= 0; i--)
        cout << ids[i] << " ";
    delete[] ids;
}

int main() {
    // 4.2 Имеется лог-файл, в котором хранятся пары для N пользователей. Напишите программу, которая
    // выбирает K пользователей, которые чаще других заходили на сайт, и выводит их в порядке возрастания посещаемости.
    int n = 0, k = 0;
    cin >> n >> k;
    Heap<pair<int, int>> heap;
    read_users(heap, n);
    show_first_users(heap, k);

    return 0;
}
