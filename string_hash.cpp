#include <iostream>
#include <vector>
using namespace std;


template<typename T, typename U>
class BKDRHash {
private:
    const T _base, _mod;
    vector<T> _pow, _pre;
public:
    BKDRHash(const U& s, T base, T mod = 1e9 + 7) : _base(base % mod), _mod(mod) {
        ssize_t n = s.size();
        _pow.resize(n + 1);
        _pow[0] = 1;
        for(ssize_t i = 0; i < n; ++i) {
            _pow[i + 1] = _pow[i] * _base % _mod;
        }

        _pre.resize(n + 1);
        for(ssize_t i = 0; i < n; ++i) {
            _pre[i + 1] = (_pre[i] * _base + s[i] % _mod) % _mod;
        }
    }

    // 0-indexed
    T hash(ssize_t p, ssize_t r) const {
        return (_pre[r + 1] - _pre[p] * _pow[r - p + 1] % _mod + _mod) % _mod;
    }

    // t appear in s ?
    bool check(const U& t) const {
        if(t.empty()) return true;

        T val = 0;
        for(auto x : t) {
            x %= _mod;
            val = (val * _base + x) % _mod;
        }

        ssize_t m = t.size(), n = _pow.size() - 1;
        for(ssize_t i = m - 1; i < n; ++i) {
            if(hash(i - m + 1, i) == val) return true;
        }
        return false;
    }
};


int main() {
    long long mod1 = 1e9 + 7, mod2 = 998244353;
    long long base1 = 23, base2 = 37;
    vector<int> nums = {1, 3 , 5, 7, 9, 2, 4, 6, 8};
    vector<int> tar = {5, 7, 9, 2};
    BKDRHash hash1(nums, base1, mod1);
    BKDRHash hash2(nums, base2, mod2);
    if(hash1.check(tar) && hash2.check(tar)) {
        cout << "YES" << endl;
    }

    string s = "135792468";
    string t = "5792";

    BKDRHash hash_s1(s, base1, mod1);
    BKDRHash hash_s2(s, base2, mod2);
    if(hash_s1.check(t) && hash_s2.check(t)) {
        cout << "YES" << endl;
    }
    return 0;
}