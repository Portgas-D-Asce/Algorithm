#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template<typename T>
T prim(const vector<vector<pair<T, T>>> &g, T mx = INT_MAX) {
    // 距离当前已经形成的最小生成树的最短距离
    vector<T> dist(g.size(), mx);
    dist[0] = 0;
    priority_queue<pair<T, T>, vector<pair<T, T>>, greater<pair<T, T>>> pq;
    pq.push({dist[0], 0});

    T total = 0;
    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if(d > dist[u]) continue;
        total += d;
        for(auto [v, w] : g[u]) {
            if(w >= dist[v]) continue;
            dist[v] = w;
            pq.push({dist[v], v});
        }
    }
    return total;
}


int main() {
    vector<vector<pair<int, int>>> g = {
        {{1, 1}, {2, 1}}, {{0, 1}, {2, 1}},
        {{0, 1}, {1, 1}, {3, 1}}, {{2, 1}}
    };
    auto dist = prim(g);
    cout << dist << endl;
    return 0;
}