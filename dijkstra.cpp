#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template<typename T>
vector<T> dijkstra(const vector<vector<pair<T, T>>>& g, T s, T mx = INT_MAX) {
    vector<T> dist(g.size(), mx);
    dist[s] = 0;

    priority_queue<pair<T, T>, vector<pair<T, T>>, greater<pair<T, T>>> pq;
    pq.push({dist[s], s});
    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        //可以使用 visited 数组，用于标记已经找到最短路径的节点
        //这里使用小优化，去掉了 visited 数组
        if(d > dist[u]) continue;
        for(auto [v, w] : g[u]) {
            T temp = d + w;
            if(temp < dist[v]) {
                dist[v] = temp;
                //松弛只是将新结果 push 到优先队列中，并没有移除之前结果
                pq.push({temp, v});
            }
        }
    }
    return dist;
}


int main() {
    vector<vector<pair<int, int>>> g = {
        {{1, 1}, {2, 1}}, {{0, 1}, {2, 1}},
        {{0, 1}, {1, 1}}, {{2, 1}}
    };
    auto dist = dijkstra(g, 3);
    for(int i = 0; i < 4; ++i) {
        cout << "3 to " << i << ": " << dist[i] << endl;
    }
    return 0;
}