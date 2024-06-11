#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Trie {
private:
    // 字符集中第一个字符
    const T _base;
    // 字符集中字符个数
    const int _m;
    vector<vector<int>> _nodes;
    vector<int> _dels;
public:
    Trie(T base, int m) : _base(base), _m(m) {
        //{base:'a', 'b', ..., cnt, end}
        _nodes.emplace_back(_m + 2);
    }

    template<typename U>
    void insert(const U &s) {
        int p = 0;
        for(auto x : s) {
            int idx = x - _base;
            if(!_nodes[p][idx]) {
                if(!_dels.empty()) {
                    int c = _dels.back();
                    _dels.pop_back();
                    _nodes[p][idx] = c;
                    //没有必要
                    //fill(nodes[c].begin(), nodes[c].end(), 0);
                } else {
                    _nodes[p][idx] = _nodes.size();
                    _nodes.emplace_back(_m + 2);
                }
            }
            p = _nodes[p][idx];
            _nodes[p][_m]++;
        }
        _nodes[p][_m + 1]++;
    }

    template<typename U>
    void erase(const U &s) {
        if(!search(s)) return;

        int p = 0;
        for(auto x : s) {
            int idx = x - _base;
            int c = _nodes[p][idx];
            //经过当前节点的个数
            if(!(--_nodes[c][_m])) {
                //没有人用该节点了，将该节点位置回收
                _dels.push_back(c);

                // 父节点设置为 0
                _nodes[p][idx] = 0;
            }
            p = c;
        }
        _nodes[p][_m + 1]--;
    }

    template<typename U>
    int search(const U &s) const {
        int p = 0;
        for(auto x : s) {
            int idx = x - _base;
            if(!_nodes[p][idx]) {
                return 0;
            }
            p = _nodes[p][idx];
        }
        return _nodes[p][_m + 1];
    }
};


int main() {
    Trie trie('a', 26);
    vector<string> ss = {
        "abcdadcd", "cccdeazxy", "aetces",
        "test", "freedom"
    };
    for(auto &s : ss) {
        trie.insert(s);
    }
    for(auto &s : ss) {
        cout << trie.search(s) << endl;
    }
    trie.erase(ss.front());
    cout << trie.search(ss.front()) << endl << endl;

    vector<vector<int>> vs = {
        {1, 3, 5, 7, 9, 11},
        {2, 4, 6, 8, 10}
    };

    Trie trie_num(0, 12);
    for(auto &v : vs) {
        trie_num.insert(v);
    }

    cout << trie_num.search(vs.front()) << endl;
    cout << trie_num.search(vs.back()) << endl;

    trie_num.erase(vs.front());
    cout << trie_num.search(vs.front()) << endl;

    return 0;
}