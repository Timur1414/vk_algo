#include <cmath>
#include <iostream>

using namespace std;

int partition(int* arr, int l, int r) {
    int pivot = rand() % (r - l + 1) + l;
    swap(arr[l], arr[pivot]);
    int i = r;
    for (int j = r; j > l; j--) {
        if (arr[j] >= arr[l]) {
            swap(arr[j], arr[i]);
            i--;
        }
    }
    swap(arr[l], arr[i]);
    return i;
}

int k_order(int* arr, int n, int k) {
    int l = 0, r = n - 1;
    int pivot_index = partition(arr, l, r);
    while (pivot_index != k) {
        if (k < pivot_index)
            r = pivot_index - 1;
        else
            l = pivot_index + 1;
        pivot_index = partition(arr, l, r);
    }
    return arr[pivot_index];
}

int percentile(int* arr, int n, int percent) {
    int k = percent * n / 100;
    return k_order(arr, n, k);
}

int main() {
    // 6.4 Реализуйте стратегию выбора опорного элемента “случайный элемент”.
    // Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
    srand(time(nullptr));
    int n;
    cin >> n;
    int* arr = new int[n];
    int* copy1 = new int[n];
    int* copy2 = new int[n];
    int* copy3 = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        copy1[i] = arr[i];
        copy2[i] = arr[i];
        copy3[i] = arr[i];
    }
    int percentile_10 = percentile(copy1, n, 10);
    int percentile_50 = percentile(copy2, n, 50);
    int percentile_90 = percentile(copy3, n, 90);
    cout << percentile_10 << endl << percentile_50 << endl << percentile_90;
    delete[] arr;
    delete[] copy1;
    delete[] copy2;
    delete[] copy3;

    return 0;
}