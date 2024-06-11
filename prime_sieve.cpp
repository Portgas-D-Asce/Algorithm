#include <iostream>
#include <vector>
using namespace std;


// return prime in [0, n]
template<typename T>
vector<T> prime_sieve(T n) {
    size_t idx = 0;
    vector<T> prime(n + 1);
    for(T i = 2; i <= n; ++i) {
        if(prime[i]) continue;
        prime[idx++] = i;
        for(T j = i + i; j <= n; j += i) {
            prime[j] = 1;
        }
    }
    prime.resize(idx);
    return prime;
}


// return prime in [0, n]
template<typename T>
vector<T> linear_sieve(T n) {
    size_t idx = 0;
    vector<T> prime(n + 1);
    for(T i = 2; i <= n; ++i) {
        if(!prime[i]) prime[idx++] = i;
        for(T j = 0; j < idx; ++j) {
            T x = prime[j] * i;
            if(x > n) break;
            // 用 prime[j] 标记 x
            prime[x] = 1;
            // prime[j] 是 i 的最小质因子
            if(i % prime[j] == 0) break;
        }
    }
    prime.resize(idx);
    return prime;
}


int main() {
    auto primes1 = prime_sieve(101);
    for(auto prime : primes1) {
        cout << prime << " ";
    }
    cout << endl;

    auto primes2 = prime_sieve(101);
    for(auto prime : primes2) {
        cout << prime << " ";
    }
    cout << endl;

    cout << (primes1 == primes2) << endl;

    return 0;
}