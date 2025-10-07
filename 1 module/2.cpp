#include <iostream>

using namespace std;

bool bin_search(int* arr, int& start, int& end, int item) {
    int l = start;
    int r = end;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == item) {
            start = mid;
            return true;
        }
        if (arr[mid] < item)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return false;
}

int exponential_search(int* arr, int end, int item) {
    int index = 1;
    while (index < end && arr[index] < item)
        index *= 2;
    return min(end - 1, index);
}

void show_intersection(int* arr1, int* arr2, int n, int m) {
    int start = 0;
    int end = exponential_search(arr1, n, arr2[m - 1]);
    for (int i = 0; i < m; i++) {
        if (bin_search(arr1, start, end, arr2[i]))
            cout << arr2[i] << " ";
    }
}

int main() {
    // 2.3 Даны два массива неубывающих целых чисел, упорядоченные по возрастанию. Найдите их пересечение.
    int n = 0, m = 0;
    cin >> n >> m;
    int* arr1 = new int[n];
    int* arr2 = new int[m];
    for (int i = 0; i < n; i++)
        cin >> arr1[i];
    for (int i = 0; i < m; i++)
        cin >> arr2[i];
    show_intersection(arr1, arr2, n, m);
    delete[] arr1;
    delete[] arr2;

    return 0;
}