#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>

using namespace std;
typedef long long ll;

const int N = 1e2;
const int inf = 1e9;
int n,m;
int c[N][N],trace[N],vis[N],d[N],ans[N];
stack<int> st;
vector<int> g[N];

void floyd(){
    int trace[N][N];
    for(int u=1;u<=n;++u){
        for(int v=1;v<=n;++v){
            trace[u][v] = v;
        }
    }
    //Floyd
    for(int k=1;k<=n;++k){
        for(int u=1;u<=n;++u){
            for(int v=1;v<=n;++v){
                if(c[u][v] > c[u][k] + c[k][v]){
                    c[u][v] = c[u][k] + c[k][v];
                    trace[u][v] = trace[u][k];
                 }
            }
        }
    }
}
void dfs_topo(int u){
    vis[u] = 1;
    for(int v : g[u]){
        if(vis[v]==1){
            cout << "Graph contains a cyclic\n";
            return void();
        }
        if(!vis[v]) dfs_topo(v);
    }
    st.push(u);
    vis[u]=2;
}
void init_create_new(int s,int f){
    for(int i=1;i<=n;++i) d[i] = inf;
    d[s] = 0;
    
    for(int i=1;i<=n;++i){
        int u = ans[i];
        for(int v : g[u]){
            if(d[v] > d[u] + c[u][v]){
                d[v] = d[u] + c[u][v];
                trace[v] = u;
            }
        }
    }
    if(d[f]==inf){
        cout << "No path\n";
        return void();
    }else{
        stack<int> xintv;
        while(f!=s){
            xintv.push(f);
            f = trace[f];
        }
        xintv.push(s);
        cout << "The shortest path of XINTV and DUCOH\n";
        while(!xintv.empty()){
            cout << xintv.top() << " ";
            xintv.pop();
        }
    }
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    //Topo ordering and shortest path
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            c[i][j] = inf;
        }
        c[i][i] = 0;
    }
    for(int i=1,u,v;i<=m;++i){
        cin>>u>>v;
        g[u].push_back(v);
        c[u][v] = 1;
    }
    c[1][2] = 100;
    for(int i=1;i<=n;++i) if(!vis[i]) dfs_topo(i);
    
    int cnt = 0;
    while(!st.empty()){
        ans[++cnt]=st.top();
        st.pop();
    }
    
    init_create_new(1, 3);
    return 0;
}
