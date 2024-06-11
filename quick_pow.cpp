/* all the function template require (mod - 1) * (mod - 1) <= T::max !!!! */

#include <iostream>
#include <vector>
using namespace std;


template<typename T>
T qpow(T a, T b, T mod = 1) {
    // input a maybe too large to cal a * a (overflow)
    a %= mod;
    T res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

template<typename T>
T super_qpow(T a, const string& s, T mod = 1) {
    T res = 1, base = 10;
    for(auto ch : s) {
        res = qpow(res, base, mod) * qpow(a, static_cast<T>(ch - '0'), mod) % mod;
    }
    return res;
}


template<typename T>
vector<vector<T>> matrix_multiple(const vector<vector<T>> &mat1, const vector<vector<T>> &mat2, T mod = 1) {
    size_t m = mat1.size(), n = mat2.size(), w = mat2[0].size();
    vector<vector<T>> res(m, vector<T>(w));
    for(size_t i = 0; i < m; ++i) {
        for(size_t j = 0; j < w; ++j) {
            for(size_t k = 0; k < n; ++k) {
                res[i][j] = (res[i][j] + (mat1[i][k] % mod) * (mat2[k][j] % mod) % mod) % mod;
            }
        }
    }
    return res;
}

template<typename T>
vector<vector<T>> matrix_qpow(vector<vector<T>> mat, T x, T mod = 1) {
    size_t n = mat.size();
    vector<vector<T>> res(n, vector<T>(n));
    for(size_t i = 0; i < n; ++i) {
        res[i][i] = 1;
    }

    while(x) {
        if(x & 1) res = matrix_multiple(res, mat, mod);
        mat = matrix_multiple(mat, mat, mod);
        x >>= 1;
    }
    return res;
}


int main() {
    long long mod = 998244353;
    cout << qpow(21ll, 2147483647ll, mod) << endl;
    cout << super_qpow(21ll, "2147483647", mod) << endl;

    vector<vector<long long>> mat = {{1, 3, 5}, {7, 9, 2}, {4, 6, 8}};
    auto res = matrix_qpow(mat, 1000ll, mod);
    for(auto &row : res) {
        for(auto x : row) {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}