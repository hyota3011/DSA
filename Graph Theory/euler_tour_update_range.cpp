#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;
const int N = 100;
const int inf = 1e9+7;
int n,m;
int h[N],en[N],tour[N],par[N],
st[N],bit[N],f[N],b[N];
vector<int> g[N];

int lca(int u,int v){
    //un optimize approach of LCA
    if(h[v] < h[u]) swap(u,v);
    int k = h[v] - h[u];
    while(k--){
        v = par[v];
    }
    if(u==v) return u;
    while(par[u]!=par[v]){
        u = par[u];
        v = par[v];
    }
    return par[u];
}


void update(int idx,int val){
    while(idx<=n){
        bit[idx]+=val;
        idx+=idx&-idx;
    }
}

void update_range(int u,int v,int val){
    update(st[u],val);
    update(st[v],val);
    int p = lca(u,v);
    update(st[p],-val);
    update(st[par[p]],-val);
}
int get(int idx){
    int ans = 0;
    while(idx){
        ans+=bit[idx];
        idx-=idx&-idx;
    }
    return ans;
}

int prefix_sum(int u){
    return get(en[u]) - get(st[u]-1);
}

void dfs(int u){
    h[u] = h[par[u]]+1;
    tour[++m] = u;
    st[u] = m;
    for(int v : g[u]){
        if(v!=par[u]){
            par[v]=u;
            dfs(v);
        }
    }
    en[u] = m;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    cin>>n>>m;
    for(int i=1,u,v;i<=m;++i){
        cin>>u>>v;
        g[u].push_back(v);
    }
    m=0;
    par[1] = 1;
    dfs(1);
    for(int i=1;i<=n;++i){
        update_range(i,i,i);
    }
    cout << "Hello World!\n";
    update_range(2,4,1);
    cout << prefix_sum(2);
    return 0;
/*
5 4
1 2
1 5
2 3
2 4
 */
}
