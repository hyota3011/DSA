#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 101;
int n,m,q,t,cnt,numSCC;
int num[N],low[N],par[N],fee[N],e[N],w[N];
stack<int> st;
vector<int> g[N];

void dfs(int u){
    num[u]=low[u]=++cnt;
    st.push(u);
    w[u] = 1;
    for(int v : g[u]){
        if(v==par[u] || !fee[v]) continue;
        if(!num[v]){
            par[v] = u;
            dfs(v);
            w[u]+=w[v];
            low[u] = min(low[u],low[v]);
        }else low[u] = min(low[u],num[v]);
    }
    if(num[u]==low[u]){
        ++numSCC;
        while(1){
            int v = st.top();
            st.pop();
            fee[v] = 0;
            ++e[numSCC];
            if(v==u) break;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    cin>>n>>m;
    for(int i=1,u,v;i<=m;++i){
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    memset(fee,1,sizeof(fee));
    par[1]=1;
    dfs(1);
    
    int sum = 0;
    for(int v=2;v<=n;++v){
        int u = par[v];
        if(low[v]>num[u]){
            //Khong ton tai cung nguoc
            sum+=w[v]*(n-w[v]);
        }
        
    }
    
    cout << sum << '\n';
    return 0;
}
