#include <iostream>
#include <queue>
#include <vector>
using namespace std;


template<typename T = int>
class Dinic {
private:
    // _n 节点个数, _s 源点, _t 汇点
    int _n, _s, _t;

    // 链式前向星 edges 数组
    // {v, capacity, next}
    vector<vector<T>> _edges;
    // 链式前向星 head 数组
    vector<int> _head;
    vector<int> _depth;
    vector<int> _cur;
public:
    Dinic(int n, int s, int t) : _n(n), _s(s), _t(t), _head(n), _depth(n), _cur(n) {
        // 从 2，3 开始，因为需要用标记 0 表示结束边
        _edges.emplace_back(3);
        _edges.emplace_back(3);
    }

    void add_edge(int u, int v, T capacity) {
        int idx = _edges.size();
        // 添加正向边
        _edges.push_back({v, capacity, _head[u]});
        _head[u] = idx++;
        // 添加反向边，容量初始化为 0
        _edges.push_back({u, 0, _head[v]});
        _head[v] = idx;
    }

    T max_flow(T init_val) {
        T flow = 0;
        while(bfs()) {
            // 重置 cur 数组
            _cur = _head;

            // 寻找阻塞流
            flow += dfs(_s, init_val);
        }
        return flow;
    }

    vector<int> min_cut() const {
        vector<int> cut(_n);
        queue<int> que;
        que.push(_s);
        cut[_s] = 1;
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int i = _head[u]; i; i = _edges[i][2]) {
                int v = _edges[i][0];
                T capacity = _edges[i][1];
                if(cut[v] != 0 && capacity) {
                    que.push(v);
                    cut[v] = 1;
                }
            }
        }
        return cut;
    }
private:
    bool bfs() {
        // 重置深度数组
        fill(_depth.begin(), _depth.end(), 0);

        queue<int> que;
        que.push(_s);
        // 需要用状态 0 表示节点的深度还没有找到，源点深度从 1 开始
        _depth[_s] = 1;
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int i = _head[u]; i; i = _edges[i][2]) {
                int v = _edges[i][0];
                T capacity = _edges[i][1];
                if(_depth[v] == 0 && capacity != 0) {
                    _depth[v] = _depth[u] + 1;
                    que.push(v);
                    // 一旦找到汇点，这里直接返回了
                    // 剩余未访问的点的深度 >= 汇点深度，遍历时不会用到
                    if(v == _t) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    // mf: 上游节点最多输送的流量
    T dfs(int u, T mf) {
        // 如果到达汇点, mf 就是最大能传递下来的流量
        if(u == _t) {
            return mf;
        }

        // 从 u 节点出发，可以到达 t 的流量总和
        T sum = 0;
        for(int i = _cur[u]; i; i = _edges[i][2]) {
            // 当前弧优化，记录 u 找到哪条边了
            _cur[u] = i;
            int v = _edges[i][0];
            T capacity = _edges[i][1];
            if(_depth[v] == _depth[u] + 1 && capacity) {
                // v 向 t 总共传输了多少流量
                T f = dfs(v, min(mf, capacity));

                // 剩余流量减去已传输流量
                _edges[i][1] -= f;
                // 反向边加上已传输流量
                _edges[i ^ 1][1] += f;

                // 累加 u 可以传输向 t 的流量
                sum += f;

                // 上游传递下来的流量还剩多少
                mf -= f;
                // 余量优化，没有剩余了直接退出
                if(!mf) {
                    break;
                }
            }
        }
        // 残枝优化
        // sum == 0 表示无法从 u 向 t 传递流量
        if(!sum) {
            _depth[u] = 0;
        }
        return sum;
    }
};


int main() {
    vector<vector<int>> edges = {
        {4, 2, 30}, {4, 3, 20}, {2, 3, 20},
        {2, 1, 30}, {1, 3, 30}
    };
    int n = 5, s = 4, t = 3;

    Dinic dinic(n, s, t);
    for(auto &edge : edges) {
        int u = edge[0], v = edge[1], c = edge[2];
        dinic.add_edge(u, v, c);
    }
    cout << dinic.max_flow(2147483647ll) << endl;

    return 0;
}
