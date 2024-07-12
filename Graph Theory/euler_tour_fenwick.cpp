#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;
const int N = 100;
const int inf = 1e9+7;
int n,cnt=0,m;
int h[N],en[N],tour[N],par[N],bit[N],w[N],st[N][17],lg2[N],xintv[N],f[N],b[N];
vector<int> g[N];
void update(int idx,int val){
    while(idx<=n){
        bit[idx]+=val;
        idx+=idx&-idx;
    }
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
    return get(en[u]) - get(xintv[u]-1);
}
void dfs(int u,int p){
    tour[++m] = u;
    xintv[u] = m;
    for(int v:g[u]){
        if(v!=p){
            dfs(v,u);
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
    dfs(1,0);
    for(int i=1;i<=n;++i) update(xintv[i],i);
    //Cap nhat dinh & truy van sum subtree
    update(xintv[2],69);
    cout << prefix_sum(2) << '\n';
    
    return 0;
/*
5 4
1 2
1 5
2 3
2 4
 */
}
