#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 201;
const int M = 40001;
int n,m,deg[N],edge_id[N][N],used_edge[M],w[M],S[M];

struct Edge {
    int target, id;
    Edge(int _target, int _id): target(_target), id(_id) {}
};

vector<Edge> g[N];

bool check_xintv(){
    for(int i=1;i<=n;++i){
        if(deg[i]&1) return false;
    }
    return true;
}

list<int> euler_walk(int u) {
    list<int> ans;
    ans.push_back(u);
    while (!g[u].empty()) {
        int v = g[u].back().target;
        int eid = g[u].back().id;
        g[u].pop_back();
        if (used_edge[eid]) continue;
        used_edge[eid] = true;
        u = v;
        ans.push_back(u);
    }
    for (auto it = ++ans.begin(); it != ans.end(); ++it) {
        auto t = euler_walk(*it);
        t.pop_back();
        ans.splice(it, t);
    }

    return ans;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    cin>>n>>m;
    for(int i=1,u,v;i<=m;++i){
        cin>>u>>v>>w[i];
        
        g[u].push_back({v,i});
        g[v].push_back({u,i});
        edge_id[u][v]=edge_id[v][u]=i;
        ++deg[u];
        ++deg[v];
    }
    if(!check_xintv()){
        cout << -1;
        return 0;
    }
    list<int> cycle = euler_walk(1);
    int cycle_size = static_cast<int>(cycle.size());
    if(cycle_size < m){
        cout << -1;
        return 0;
    }
    memset(S,0,sizeof(S));
    int u = *cycle.begin();
    auto it = ++cycle.begin();
    for (int i = 1; it != cycle.end(); ++i, ++it) {
        int v = *it;
        S[i] = S[i - 1] + w[edge_id[u][v]];
        u = v;
    }

    int k = 0;
    for (int i = 1; i < cycle_size; ++i)
        if (S[i] < S[k]) k = i;

    list<int> ans;
    ans.clear();
    it = cycle.begin();
    for (int i = 0; i < k; ++i, ++it)
        ans.push_back(*it);
    ans.push_back(*it);
    ans.insert(ans.begin(), it, (--cycle.end()));

    for (int i : ans) cout << i << " ";
    return 0;
}
