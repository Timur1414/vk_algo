#include <iostream>

using namespace std;

class Stack {
private:
    int size;
    int capacity;
    int* arr;
public:
    Stack() {
        size = 0;
        capacity = 1;
        arr = new int[capacity];
    }
    ~Stack() {
        delete[] arr;
    }
    Stack(const Stack&) = delete;
    Stack(Stack&&) = delete;

    Stack& operator=(const Stack&) = delete;
    Stack& operator=(Stack&&) = delete;

    int pop() {
        if (size == 0)
            return -1;
        return arr[--size];
    }
    int top() {
        if (size == 0)
            return -1;
        return arr[size - 1];
    }
    void push(int x) {
        if (size + 1 > capacity) {
            capacity *= 2;
            int* new_arr = new int[capacity];
            for (int i = 0; i < size; i++)
                new_arr[i] = arr[i];
            delete[] arr;
            arr = new_arr;
        }
        arr[size++] = x;
    }
    bool empty() const {
        return size == 0;
    }
};

class Queue {
private:
    Stack in;
    Stack out;
    int size;
public:
    Queue() {
        size = 0;
    }
    ~Queue() = default;
    Queue(const Queue&) = delete;
    Queue(Queue&&) = delete;

    Queue& operator=(const Queue&) = delete;
    Queue& operator=(Queue&&) = delete;

    int pop() {
        int res = first();
        out.pop();
        if (res != -1)
            size--;
        return res;
    }
    int first() {
        if (size == 0)
            return -1;
        if (out.empty())
            while (!in.empty()) {
                int x = in.pop();
                out.push(x);
            }
        return out.top();
    }
    void push(int x) {
        size++;
        in.push(x);
    }
    bool empty() const {
        return size == 0;
    }
};

void main_logic(Queue& queue, int n, bool& result) {
    for (int i = 0; i < n; i ++) {
        int a = 0, b = 0;
        cin >> a >> b;
        if (a == 2) {
            int item = queue.pop();
            if (item != b)
                result = false;
        }
        else
            queue.push(b);
    }
}

int main() {
    // 3.3 Очередь через 2 стека.
    Queue queue;
    int n = 0;
    cin >> n;
    bool result = true;
    main_logic(queue, n, result);
    cout << (result ? "YES" : "NO");

    return 0;
}
