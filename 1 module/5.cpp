#include <iostream>

using namespace std;

bool operator<(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
}

template <typename T>
void merge(T* arr, int left, int mid, int right) {
    int size1 = mid - left + 1;
    int size2 = right - mid;
    T* left_arr = new T[size1];
    for (int i = 0; i < size1; i++)
        left_arr[i] = arr[left + i];
    T* right_arr = new T[size2];
    for (int i = 0; i < size2; i++)
        right_arr[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < size1 && j < size2) {
        if (left_arr[i] < right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        }
        else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }
    while (i < size1) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }
    while (j < size2) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
    delete[] left_arr;
    delete[] right_arr;
}

template <typename T>
void merge_sort(T* arr, int left, int right) {
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

template <typename T>
void read_segments(T* arr, int n) {
    for (int i = 0; i < n; i++) {
        int l = 0, r = 0;
        cin >> l >> r;
        pair<int, int> segment = make_pair(l, r);
        arr[i] = segment;
    }
}

template <typename T>
int calculate_length(T* arr, int n, int length, int last_r) {
    for (int i = 1; i < n; i++) {
        if (arr[i].first < last_r) {
            if (arr[i].second > last_r) {
                length += arr[i].second - last_r;
                last_r = arr[i].second;
            }
        }
        else {
            length += arr[i].second - arr[i].first;
            last_r = arr[i].second;
        }
    }
    return length;
}

int main() {
    // 5.3 Известны координаты левого и правого концов каждого отрезка. Найти длину окрашенной части.
    int n = 0;
    cin >> n;
    if (n == 0) {
        cout << 0;
        return 0;
    }
    pair<int, int>* arr = new pair<int, int>[n];
    read_segments<pair<int, int>>(arr, n);
    merge_sort(arr, 0, n - 1);
    int length = arr[0].second - arr[0].first;
    int last_r = arr[0].second;
    length = calculate_length<pair<int, int>>(arr, n, length, last_r);
    cout << length;
    delete[] arr;

    return 0;
}
