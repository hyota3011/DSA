#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 801;

int n,m,cnt,numSCC,num[N],low[N],fee[N],vis[N],component[N],br[N];
vector<int> g[N],ls[N];
stack<int> st;

void dfs(int u){
    num[u]=low[u]=++cnt;
    st.push(u);
    for(int v:g[u]){
        if(!fee[v]) continue;
        if(!num[v]){
            dfs(v);
            low[u] = min(low[u],low[v]);
        }else low[u] = min(low[u],num[v]);
    }
    if(num[u]==low[u]){
        ++numSCC;
        while(1){
            int v = st.top();
            st.pop();
            fee[v] = 0;
            ls[numSCC].push_back(v);
            component[v] = numSCC;
            if(u==v) break;
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    cin>>n>>m;
    for(int i=1,u,v;i<=m;++i){
        cin>>u>>v;
        g[u].push_back(v);
    }
    memset(fee,1,sizeof(fee));
    for(int i=1;i<=n;++i){
        if(!num[i]) dfs(i);
    }
    for(int i=1;i<=n;++i){
        for(int j=0;j<static_cast<int>(g[i].size());++j){
            int v = g[i][j];
            if(component[i]!=component[v]) br[component[v]] = 1;
        }
    }
    int cnt = 0;
    for(int i=1;i<=numSCC;++i){
        if(!br[i]) ++cnt;
    }
    cout << cnt << '\n';
    return 0;
}
