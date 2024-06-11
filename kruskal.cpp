#include <iostream>
#include <queue>
#include <vector>
using namespace std;

size_t find(vector<size_t> &uf, size_t x) {
    return uf[x] == x ? x : (uf[x] = find(uf, uf[x]));
}

template<typename T>
T kruskal(vector<vector<T>> &edges, size_t n) {
    int total = 0;
    vector<size_t> uf(n);
    for(size_t i = 0; i < n; ++i) {
        uf[i] = i;
    }

    sort(edges.begin(), edges.end());

    size_t cnt = 0;
    for(int i = 0; i < edges.size(); ++i) {
        T w = edges[i][0], u = edges[i][1], v = edges[i][2];
        size_t pu = find(uf, u), pv = find(uf, v);
        if(pu == pv) continue;
        if(++cnt == n) break;
        total += w;
        uf[pu] = pv;
    }
    return total;
}


int main() {
    vector<vector<int>> edges = {{1, 1, 0}, {1, 1, 2}, {1, 0, 2}, {1, 2, 3}};
    auto dist = kruskal(edges, 4);
    cout << dist << endl;
    return 0;
}