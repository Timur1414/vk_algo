#include <iostream>

using namespace std;

int get_k_bit(int n, int k) {
    n = n >> k;
    return (n & 1);
}

int main() {
    // 1.2 Вернуть значение бита в числе N по его номеру K.
    int n = 0, k = 0;
    cin >> n >> k;
    cout << get_k_bit(n, k);


    return 0;
}
