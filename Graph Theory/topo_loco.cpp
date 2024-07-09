#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
typedef long long ll;
const int N = 1001;
const int xintv = 1e9+1;
int n,m,id,trace[N],vis[N],q[N],num[N],f[N];
int arr[N],g[N][N],a[N];
map<int,int> rev;
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

void two_pointer(){
    for(int i=3;i<=n;++i){
        int u = 1,v = n;
        while(u<v){
            if(a[u] + a[v] > a[i]){
                --v;
            }else if(a[u] + a[v] < a[i]){
                ++u;
            }else{
                g[rev[a[u]]][rev[a[i]]] = g[rev[a[v]]][rev[a[i]]] = 1;
                u++;
                v--;
            }
        }
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>arr[i];
        a[i]=arr[i];
        rev[a[i]] = i;
    }
    sort(a+1,a+n+1);
    
    two_pointer();
    
    id = n;
    for(int i=1;i<=n;++i) if(!vis[i]) dfs(i);
    for(int i=n-1;i>=1;--i){
        int k = 0;
        for(int j=i+1;j<=n;++j){
            if(g[q[i]][q[j]]){
                k = max(k,f[j]+1);
            }
            f[i] = k;
        }
    }
    int k = 0;
    for(int i=1;i<=n;++i){
        k = max(k,f[i]);
    }
    cout << k + 1 << '\n';
    return 0;
}
