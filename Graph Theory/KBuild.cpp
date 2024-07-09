#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 1001;
int n,m,q,t,cnt,bridges;
int num[N],low[N],mark[N],nC[N],par[N];
int g[N][N];

void dfs(int u){
    num[u]=low[u]=++cnt;
    mark[u]=false;
    for(int v=1;v<=n;++v){
        if(g[u][v]){
            if(v==par[u]) continue;
            if(!num[v]){
                par[v] = u;
                dfs(v);nC[v]++;
                mark[u]|= low[v]>=num[u];
                if(low[v] > num[u]){
                    ++bridges;
                }
                low[u] = min(low[u],low[v]);
                
            }else low[u] = min(low[u],num[v]);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    cin>>n;
    m = n-1;
    for(int i=1,u,v;i<=m;++i){
        cin>>u>>v;
        g[u][v]=g[v][u]=1;
    }
    cin>>q;
    while(q--){
        int a,b;
        cin>>a>>b;
        g[a][b]=g[b][a]=1;
    }
    dfs(1);
    cout << bridges << '\n';
    return 0;
}
