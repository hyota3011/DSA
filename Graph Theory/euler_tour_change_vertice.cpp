#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;
const int N = 100;
const int inf = 1e9+7;
int n,cnt=0,m;
int h[N],en[N],tour[N],par[N],bit[N],w[N],st[N][17],lg2[N],xintv[N],f[N];
vector<int> g[N];

void dfs(int u,int p){
    tour[++m] = u;
    xintv[u] = m;
    for(int v:g[u]){
        if(v!=p){
            dfs(v,u);
        }
    }
    tour[++m] = u;
    en[u] = m;
}

void init_view_detail(){
    lg2[1] = 0;
    for(int i=1;i<=N;++i){
        lg2[i] = lg2[i>>1] + 1;
    }
    //Sparse Table
    for(int k=1;1<<k<=cnt;++k){
        for(int j=1;j + (1<<k) - 1 <=cnt;++j ){
            st[j][k] = (h[st[j][k-1]] < h[st[j+(1<<(k-1))][k-1]] ? st[j][k-1] : st[j + (1<<(k-1)) ][k-1]);
        }
    }
}
int query(int l,int r){
    int k = lg2[r-l+1];
    return (h[st[l][k-1]] < h[st[l+(1<<(k-1))][k-1]] ? st[l][k-1] : st[l + (1<<(k-1)) ][k-1]);
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    cin>>n>>m;
    for(int i=1,u,v;i<=m;++i){
        cin>>u>>v;
        g[u].push_back(v);
    }
    dfs(1,0);
    for(int i=1;i<=n;++i){
        f[xintv[i]] = i;
        f[en[i]] = - f[xintv[i]];
    }
    f[xintv[2]]+=100;
    f[en[2]]-=100;
    int sum = 0;
    for(int i=xintv[1];i<=xintv[4];++i){
        sum+=f[i];
    }
    cout << sum << '\n';
    return 0;
/*
5 4
1 2
1 5
2 3
2 4
 */
}
