/* (p - 1) * (p - 1) <= T::max */

#include <iostream>
#include <vector>
using namespace std;


// p must be prime
template<typename T>
T fermat_inv(T a, T p) {
    a %= p;
    T b = p - 2, res = 1;
    while(b) {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

// must gcd(a, b) == 1, final result is x
template<typename T>
pair<T, T> exgcd(T a, T b) {
    if(b == 0) return {1, 0};
    auto [x, y] = exgcd(b, a % b);
    return {y, x - a / b * y};
}

template<typename T>
T exgcd_inv(T a, T b) {
    auto [x, _] = exgcd(a, b);
    return (x % b + b) % b;
}

// p must be prime
template<typename T>
vector<T> linear_inv(T p) {
    vector<T> inv(p);
    inv[1] = 1;
    for(T i = 2; i < p; ++i) {
        // make inv[i] > 0
        inv[i] = (p - p / i) * inv[p % i] % p;
    }
    return inv;
}


int main() {
    cout << fermat_inv(10, 23) << endl;

    cout << exgcd_inv(9, 10) << endl;

    auto inv = linear_inv(17);
    for(int i = 0; i < 17; ++i) {
        cout << inv[i] << " ";
    }
    cout << endl;

    return 0;
}