#include <iostream>
#include <vector>
using namespace std;


class BinaryTrie {
private:
    constexpr static int _m = 3;
    constexpr static int _cnt = _m - 1;
    // 每个数字多少位
    const int _n;
    vector<vector<int>> _nodes;
    vector<int> _dels;

public:
    explicit BinaryTrie(int n = 20) : _n(n){
        // [0, 2 ^ (n + 1) - 1]
        //{'0', '1', cnt}
        _nodes.emplace_back(_m);
    }

    template<typename T>
    void insert(T x) {
        int p = 0;
        for(int i = 0; i <= _n; ++i) {
            T idx = (x >> (_n - i)) & 1;
            if(!_nodes[p][idx]) {
                if(!_dels.empty()) {
                    T c = _dels.back();
                    _dels.pop_back();
                    _nodes[p][idx] = c;
                } else {
                    _nodes[p][idx] = _nodes.size();
                    _nodes.emplace_back(_m);
                }
            }
            p = _nodes[p][idx];
            _nodes[p][_cnt]++;
        }
    }

    template<typename T>
    void erase(T x) {
        if(!search(x)) return;
        T p = 0;
        for(int i = 0; i <= _n; ++i) {
            T idx = (x >> (_n - i)) & 1;
            T c = _nodes[p][idx];
            if(!(--_nodes[c][_cnt])) {
                _dels.push_back(c);
                _nodes[p][idx] = 0;
            }
            p = c;
        }
    }

    template<typename T>
    int search(T x) const {
        T p = 0;
        for(int i = 0; i <= _n; ++i) {
            T idx = (x >> (_n - i)) & 1;
            if(!_nodes[p][idx]) {
                return 0;
            }
            p = _nodes[p][idx];
        }
        return _nodes[p][_cnt];
    }

    template<typename T>
    T max_xor(const T x) {
        T res = 0;
        T p = 0;
        for(int i = 0; i <= _n; ++i) {
            res <<= 1;
            bool idx = (x >> (_n - i)) & 1;
            T c = _nodes[p][idx];
            if(_nodes[p][!idx]) {
                c = _nodes[p][!idx];
                res |= 1;
            }
            p = c;
        }
        return res;
    }
};


int main() {
    vector<int> nums = {1, 2, 3, 2, 4, 5, 7, 9};
    BinaryTrie bt(20);
    for(int x : nums) {
        bt.insert(x);
    }
    for(int x : nums) {
        cout << bt.search(x) << endl;
    }
    bt.erase(4);
    cout << bt.search(4) << endl;

    cout << bt.max_xor(5) << endl;
    return 0;
}