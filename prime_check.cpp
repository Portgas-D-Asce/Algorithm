#include <iostream>
using namespace std;


template<typename T>
bool is_prime(T x) {
    if(x == 0 || x == 1) return false;
    if(x % 2 == 0) return x == 2;
    for(T i = 3; i * i <= x; i += 2) {
        if(x % i == 0) return false;
    }
    return true;
}


int main() {
    cout << is_prime(0) << endl;
    cout << is_prime(1) << endl;
    cout << is_prime(2) << endl;
    cout << is_prime(3) << endl;
    cout << is_prime(101) << endl;
    return 0;
}