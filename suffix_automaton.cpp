#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

template<typename T>
class SuffixAutomaton {
private:
    constexpr static int _dummy = 0;
    constexpr static int _root = 1;
    const T _base;
    const int _m, _len, _link, _cnt;
    // last 有两层含义：最长子串所在的节点，第一个后缀节点
    int _last;
    vector<vector<int>> _nodes;
public:
    SuffixAutomaton(T base, int m) : _base(base), _m(m + 3), _len(m), _link(m + 1), _cnt(m + 2) {
        // base:a, b, ..., z, len, link, cnt
        // dummy
        _nodes.emplace_back(_m);
        // root
        _nodes.emplace_back(_m);
        _last = 1;
    }

    void extend(T x) {
        int cur = _nodes.size();
        // 添加一个节点，这个节点代表了最长子串
        _nodes.emplace_back(_m);
        // 最长子串的出现次数是 1
        _nodes[cur][_cnt] = 1;
        // 节点最长子串的长度为上一次最长子串的长度 + 1
        _nodes[cur][_len] = _nodes[_last][_len] + 1;

        int idx = x - _base;
        int p = _last;
        // 后缀节点更新为 cur 节点
        _last = cur;
        // 在之前后缀的基础上加上新字符，即可得到新的子串
        while(p != _dummy && !_nodes[p][idx]) {
            // 从后缀节点向新节点建一条转移边
            _nodes[p][idx] = cur;
            // 指向上一个后缀节点
            p = _nodes[p][_link];
        }

        // p = 0 说明是一个新字符
        if(p == _dummy) {
            // 新字符时，cur 节点的 link 显然应该指向根节点
            _nodes[cur][_link] = _root;
            return;
        }

        // 如果不是新字符
        /*
        p = 2, q = 4, last = 5
        node_2 = {a}, node_5 = {aaba, aba, ba}, link_5 = 2
        node_4 = {aab, ab, b}, node_6 = {aabab, abab, bab}, link_6 ? 4

        第一个后缀节点 last = node_5 表示后缀 aaba, aba, ba 出现的次数都是 1

        添加一个字符 b 后, node_6 变为第一个后缀节点, 对 node_5 的每个后缀加上 b
        得到 {aabab, abab, bab} 也就是新的后缀, 这些后缀的出现次数都是 1

        node_5 的 link 是 node_2, node_2 沿着转移边 b 到达 node_4
        如果 node_4 = {ab, b}, 那么很好, node_4 作为 node_6 的 link 正好合适

        可惜 node_4 = {aab, ab, b}, aab 不是 bab 的后缀, 无法建立 link
        从 node_4 的角度来看, 原来 aab, ab, b 出现次数相同, 现在 ab, b 出现次数增加了
        需要把 node_4 分离成两部分 node_4 = {aab}, node_7 = {ab, b}
        node_4 的 link 设置为 node_7, node_6 的 link 恰好也为 node_7
        */

        int q = _nodes[p][idx];
        // 如果 node_4 = {ab, b}, 那么很好, node_4 作为 node_6 的 link 正好合适
        if(_nodes[q][_len] == _nodes[p][_len] + 1) {
            _nodes[cur][_link] = q;
            return;
        }

        // 可惜 node_4 = {aab, ab, b}, aab 不是 bab 的后缀, 无法建立 link
        int clone = _nodes.size();
        // 添加克隆节点 node_7
        _nodes.push_back(_nodes[q]);
        // node_7 的 len 为 node_2 的 len 加 1
        _nodes[clone][_len] = _nodes[p][_len] + 1;
        // node_7 的 link 设置为 node_4 的 link, 由于是拷贝, 故不必重复修改
        // nodes[clone][_link] = nodes[q][_link];
        // 克隆节点本身不参与计数
        _nodes[clone][_cnt] = 0;

        // 原来 node_2 经转移边 b 到达 node_4 形成子串 ab
        // 原来 node_1 经转移边 b 到达 node_4 形成子串 b
        // 现在子串 ab, b 已经分给 node_7 管理了, 因此需要修改转移边
        // 现在 node_2 经转移边 b 到达 node_7 形成子串 ab
        // 现在 node_1 经转移边 b 到达 node_7 形成子串 b
        while(p != _dummy && _nodes[p][idx] == q) {
            _nodes[p][idx] = clone;
            p = _nodes[p][_link];
        }
        // node_4 的 link 为 node_7
        _nodes[q][_link] = clone;
        // node_6 的 link 也设置为 node_7
        _nodes[cur][_link] = clone;
    }

    // 父节点是子节点的后缀，父节点出现的位置是所有子节点出现的位置的并集 + 自己单独出现的位置
    // 叶子节点只出现一次，自己单独出现的位置
    vector<int> count() const {
        int n = _nodes.size();
        // 不能修改 node 节点中的 cnt, 否则下次无法 count
        vector<int> cnt(n), indeg(n);
        for(int i = _root; i < n; ++i) {
            indeg[_nodes[i][_link]]++;
            cnt[i] = _nodes[i][_cnt];
        }
        queue<int> que;
        for(int i = _root; i < n; ++i) {
            if(!indeg[i]) que.push(i);
        }

        while(!que.empty()) {
            int u = que.front(), v = _nodes[u][_link];
            que.pop();
            if(!--indeg[v]) que.push(v);
            cnt[v] += cnt[u];
        }
        return cnt;
    }

    // 统计不同非空子串的个数
    int total() const {
        int n = _nodes.size();
        // 不能修改 node 节点中的 cnt, 否则下次无法 count
        vector<int> indeg(n);
        for(int i = _root; i < n; ++i) {
            indeg[_nodes[i][_link]]++;
        }
        queue<int> que;
        for(int i = _root; i < n; ++i) {
            if(!indeg[i]) que.push(i);
        }

        int total = 0;
        while(!que.empty()) {
            int u = que.front(), v = _nodes[u][_link];
            que.pop();
            if(!--indeg[v]) que.push(v);
            total += _nodes[u][_len] - _nodes[v][_len];
        }
        return total;
    }

    vector<vector<int>> link_tree() const {
        int n = _nodes.size();
        vector<vector<int>> tree(n);
        for(int i = _root; i < n; ++i) {
            int u = _nodes[i][_link];
            tree[u].push_back(i);
        }
        return tree;
    }
};


int main() {
    string s = "aababa";

    SuffixAutomaton<char> sam('a', 26);
    for(char ch : s) {
        sam.extend(ch);
    }
    cout << sam.total() << endl;
    auto v1 = sam.count();
    auto v2 = sam.count();
    if(v1 == v2) {
        cout << "Yes" << endl;
    }
    return 0;
}
