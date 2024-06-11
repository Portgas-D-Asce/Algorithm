#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;


template<typename T>
class AcAutomaton {
private:
    constexpr static int _dummy = 0;
    constexpr static int _root = 1;
private:
    const T _base;
    const int _m, _cnt, _end, _id, _fail, _super;
    vector<vector<int>> _nodes;
    vector<int> _topo;
public:
    AcAutomaton(T base, int m) : _base(base), _m(m + 5), _cnt(m),
        _end(m + 1), _id(m + 2), _fail(m + 3), _super(m + 4) {
        _nodes.emplace_back(_m, _root);
        _nodes.emplace_back(_m);
        _nodes.back()[_super] = _root;
    }

    template<typename U>
    void build(const U &ss) {
        int n = ss.size();
        for(int i = 0; i < n; ++i) {
            insert(ss[i], i + 1);
        }

        _nodes[_root][_cnt] = n;
        _topo = vector<int>();

        queue<int> que;
        que.push(_root);
        while(!que.empty()) {
            int p = que.front();
            if(_nodes[p][_end]) {
                _topo.push_back(p);
            }
            que.pop();
            for(int i = 0; i < _cnt; ++i) {
                if(_nodes[p][i] == _dummy) {
                    continue;
                }
                int c = _nodes[p][i];

                int idx = _nodes[p][_fail];
                while(_nodes[idx][i] == _dummy) {
                    idx = _nodes[idx][_fail];
                }
                _nodes[c][_fail] = _nodes[idx][i];

                idx = _nodes[c][_fail];
                _nodes[c][_super] = _nodes[idx][_end] ? idx : _nodes[idx][_super];
                que.push(c);
            }
        }
    }

    template<typename U>
    vector<int> match(const U &s) {
        int p = _root;
        vector<int> res(_nodes[_root][_cnt]);

        int n = s.size();
        for(int i = 0; i < n; ++i) {
            int idx = s[i] - _base;
            while(_nodes[p][idx] == _dummy) {
                p = _nodes[p][_fail];
            }
            p = _nodes[p][idx];

            int pattern = _nodes[p][_super];
            if(_nodes[p][_end]) {
                pattern = p;
            }
            if(pattern != _root) {
                res[_nodes[pattern][_id] - 1]++;
            }
        }
        n = _topo.size();
        for(int i = n - 1; i >= 0; --i) {
            int cur = _topo[i];
            int pre = _nodes[cur][_super];
            if(pre == _root) continue;

            int cid = _nodes[cur][_id] - 1;
            int pid = _nodes[pre][_id] - 1;
            res[pid] += res[cid];
        }
        return res;
    }

private:
    template<typename U>
    void insert(const U &s, int sid) {
        int p = _root;
        for(auto x : s) {
            int idx = x - _base;
            if(_nodes[p][idx] == _dummy) {
                _nodes[p][idx] = _nodes.size();
                _nodes.emplace_back(_m);
            }
            p = _nodes[p][idx];
            _nodes[p][_cnt]++;
        }

        _nodes[p][_end]++;

        if(!_nodes[p][_id]) {
            _nodes[p][_id] = sid;
        }
    }
};


int main() {
    vector<string> ss = {
        "test", "aabc", "code",
        "acautomaton", "string"
    };

    AcAutomaton<char> ac('a', 26);
    ac.build(ss);
    string t = "testestaabcodeaabcstrinsgstring";
    auto res = ac.match(t);
    for(int i = 0; i < res.size(); ++i) {
        cout << ss[i] << ": " << res[i] << endl;
    }
    return 0;
}
