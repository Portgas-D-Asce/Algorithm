#include <iostream>
#include <vector>
using namespace std;


template<typename T>
vector<T> factorize(T x) {
    vector<T> factors;
    while(!(x & 1)) {
        factors.push_back(2);
        x >>= 1;
    }

    for(T i = 3; i * i <= x; i += 2) {
        while(x % i == 0) {
            factors.push_back(i);
            x /= i;
        }
    }

    if(x != 1) {
        factors.push_back(x);
    }
    return factors;
}


int main() {
    long long n = (1ll << 31) - 1;
    auto factors = factorize(2 * 2 * 3 * 7 * 101 * n);
    for(auto x : factors) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}