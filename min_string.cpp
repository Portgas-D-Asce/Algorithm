#include <iostream>
#include <string>
#include <vector>
using namespace std;

template<typename T, typename Comp = less<typename T::value_type>>
size_t min_string(const T& s, Comp cmp = Comp()) {
    size_t n = s.size(), i = 0, j = 1, k = 0;
    while(i < n && j < n && k < n) {
        size_t x = (i + k) % n, y = (j + k) % n;
        if(s[x] == s[y]) {
            ++k;
            continue;
        }
        if(!cmp(s[x], s[y])) {
            i = max(i + k + 1, j + 1);
            swap(i, j);
        } else {
            j = j + k + 1;
        }
        k = 0;
    }
    return i;
};


int main() {
    string s = "abcdacdcaadc";
    auto idx = min_string(s, greater<char>());
    rotate(s.begin(), s.begin() + idx, s.end());
    cout << s << endl;
    return 0;
}