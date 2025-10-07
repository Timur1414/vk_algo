#include <iostream>

using namespace std;

int get_k_bit(unsigned long long n, int k) {
    n = n >> k;
    return (n & 1);
}

void q_sort(unsigned long long* arr, int l, int r, int position) {
    if (l >= r || position < 0)
        return;
    int i = l, j = r;
    while (i <= j) {
        while (i <= r && get_k_bit(arr[i], position) == 0)
            i++;
        while (j >= l && get_k_bit(arr[j], position) == 1)
            j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    q_sort(arr, l, j, position - 1);
    q_sort(arr, i, r, position - 1);
}

int main() {
    // 7.3 Отсортировать массив методом MSD по битам (бинарный QuickSort).
    int n;
    cin >> n;
    unsigned long long* arr = new unsigned long long[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    q_sort(arr, 0, n - 1, 63);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    delete[] arr;

    return 0;
}
