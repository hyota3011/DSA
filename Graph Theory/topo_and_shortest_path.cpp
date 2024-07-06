#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;
typedef long long ll;
const int N = 20;
const int inf = 1e9+7;
int n,m,vis[N],ans[N],trace[N],dp[N],d[N],w[N][N];
int revTopo[N];
vector<int> g[N];
stack<int> topo;

void dfs(int u){
    vis[u] = 1;
    for(auto v : g[u]){
        if(vis[v]==1){
            cout << "Error: Graph contains a cyclic\n";
            return void();
        }
        if(!vis[v]) dfs(v);
    }
    topo.push(u);
    vis[u] = 2;
}
void find_path(int s,int f){
    s = ans[s];
    f = ans[f];
    //f(x)
    for(int i=0;i<=n;++i) d[i] = inf;
    d[s] = 0;
    
    for(int i=s;i<n;++i){//Dynamic programming
        for(int j=i+1;j<=n;++j){
            int u =i,v=j;
            //i < j =>
            if(d[v] > d[u] + w[revTopo[i]][revTopo[j]]){
                d[v] = d[u] + w[revTopo[i]][revTopo[j]];
                trace[v] = u;
            }
        }
    }
    //Trace
    printf("Shortest path %d\n",d[f]);
    vector<int> res;
    while(f!=s){
        res.push_back(revTopo[f]);
        f=trace[f];
    }
    res.push_back(revTopo[s]);
    reverse(res.begin(),res.end());
    for(const int x : res) cout << x << " ";
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    cin>>n>>m;
    
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            w[i][j] = inf;
        }
    }
    
    for(int i=1,u,v;i<=m;++i){
        cin>>u>>v;
        g[u].push_back(v);
        w[u][v] = (u==v?0:1);
    }
    for(int i=1;i<=n;++i) if(!vis[i]) dfs(i);
    int cnt = 0;
    while(!topo.empty()){
        ++cnt;
        ans[topo.top()] = cnt;
        topo.pop();
    }
    for(int i=1;i<=n;++i){
        revTopo[1] = 1;
        revTopo[ans[i]] = i;
    }
    find_path(7,3);
    
    /*
 7 7
 1 2
 1 4
 2 3
 4 5
 6 5
 5 3
 7 4
     */
    return 0;
}
