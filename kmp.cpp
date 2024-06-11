#include <iostream>
#include <string>
#include <vector>
using namespace std;


template<typename T>
ssize_t kmp(const T& s, const T& t) {
    ssize_t m = s.size(), n = t.size();
    vector<ssize_t> next(n + 1, -1);
    for(ssize_t i = 0, j = -1; i < n; ) {
        if(j == -1 || t[i] == t[j]) {
            next[++i] = ++j;
        } else {
            j = next[j];
        }
    }

    for(ssize_t i = 0, j = 0; i < m && j < n; ) {
        if(j == -1 || s[i] == t[j]) {
            ++i, ++j;
            if(j == n) return i - j;
        } else {
            j = next[j];
        }
    }
    return -1;
}


int main() {
    string s = "aabcdacdcadc", t = "bcdacd";
    ssize_t idx = kmp(s, t);
    cout << idx << endl;
    cout << s.substr(idx, t.size()) << endl;

    vector<int> x = {1, 3, 5, 7, 9, 2, 4, 6, 8};
    vector<int> y = {7, 9, 2, 4, 6};
    ssize_t idx1 = kmp(x, y);
    cout << idx1 << endl;
    return 0;
}