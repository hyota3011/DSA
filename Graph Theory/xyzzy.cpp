#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 1e5 + 3;
const long long INF = 0x3f3f3f3f;

int n,m,d[N],w[N],ncyc[N];
vector<pair<int,int>> adj[N];

void bellmann_ford(int s) {
    for(int i=0;i<=n;++i){
        d[i] = INF;
        ncyc[i] = false;
    }
    d[s] = 0;
    for (int iter = 0; iter < n - 1; ++iter) {
        for (int u = 0; u < n; ++u)
            if (d[u] < INF)
                for (auto &e : adj[u]){
                    int v = e.first, w = e.second;
                    if (d[u] + w < 0) d[v] = min(d[v], d[u] + w);
                }
    }
    for (int u = 0; u < n; ++u) {
        if (d[u] == INF) continue;
        for (auto &e : adj[u]) {
            int v = e.first, w = e.second;
            if (d[v] > d[u] + w && !ncyc[v] && (d[u] + w < 0)) {
                d[v] = -INF;
                ncyc[v] = true;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (true) {
        cin >> n;
        if (n == -1) break;
        memset(w,0,sizeof(w));
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
            cin >> w[i] >> m;
            for (int j = 0,k; j < m; ++j) {
                cin >> k;
                adj[i].push_back({k, 0});
            }
        }
        adj[0].clear();
        adj[0].push_back({1, -w[1] - 100});
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < adj[i].size(); ++j)
                adj[i][j].second = -w[adj[i][j].first];
        }
        bellmann_ford(0);
        
        if (ncyc[n] || d[n] < 0) cout << "winnable\n";
        else cout << "hopeless\n";
    }
    return 0;
}
