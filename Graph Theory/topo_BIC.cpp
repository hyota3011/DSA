#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;
typedef long long ll;
const int N = 101;
int n,m,id,trace[N],vis[N],q[N],f[N],num[N],t[N];
int g[N][N];
void dfs(int u){
    vis[u] = 1;
    for(int v=1;v<=n;++v){
        if(!g[u][v]) continue;
        if(vis[v]==1){
            cout << "inf\n";
            exit(0);
        }
        if(!vis[v]) dfs(v);
    }
    vis[u] = 2;
    num[u] = id;
    q[id--] = u;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    cin>>n>>m;
    for(int i=1,u,v;i<=m;++i){
        cin>>u>>v;
        ++g[u][v];
    }
    int s=1,t=2; id = n;
    for(int i=1;i<=n;++i) if(!vis[i]) dfs(i);
    f[num[t]] = 1;
    //start at 1 -> 2
    for(int i=num[t]-1;i>=num[s];--i){
        int k = 0;
        for(int j=i+1;j<=n;++j){
            if(g[q[i]][q[j]]) k+=g[q[i]][q[j]]*f[j];
        }
        f[i] = k;
    }
    cout << f[num[s]] << '\n';
    return 0;
}
