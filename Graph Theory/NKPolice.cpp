#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 1001;
int n,m,q,t;
int num[N],low[N],joint[N],par[N][17],mark[N],nC[N],tail[N],h[N];
int cnt, g[N][N],br[N][N];

bool check_sub_tree(int u,int root){
    return num[root] <= num[u] and num[u] <= tail[root];
}
bool solve1(int a,int b,int g1, int g2){
    if(num[g1] > num[g2]) swap(g1,g2);
    if(!br[a][b]) return true;
    if (check_sub_tree(a, g2) && !check_sub_tree(b, g2)) return false;
    if (check_sub_tree(a, g1) && !check_sub_tree(b, g1)) return false;
    return true;
}
int find_par(int u,int p){
    for(int i=16;i>=0;--i)
        if(h[par[u][i]] > h[p]) u = par[u][i];
    return u;
}
bool solve2(int a,int b,int c){
    if(!mark[c]) return true;
    int pa = 0; pa = find_par(a,c);
    int pb = 0; pb = find_par(b,c);
    
    if(!pa && !pb) return true;
    
    if(pa==pb) return true;
    if(!pa && low[pb] < num[c]) return true;
    if(!pb && low[pa] < num[c]) return true;
    if(low[pa] < num[c] and low[pb] < num[c]) return true;
    return false;
}
void dfs(int u){
    num[u]=low[u]=tail[u]=++cnt;
    mark[u]=false;
    for(int v=1;v<=n;++v){
        if(g[u][v]){
            if(v==par[u][0]) continue;
            if(!num[v]){
                h[v] = h[u] + 1;
                par[v][0] = u;
                for(int j=1;j<17;++j){
                    par[v][j] = par[par[v][j-1]][j-1];
                }
                
                dfs(v);nC[v]++;
                mark[u]|= low[v]>=num[u];
                if(low[v] > num[u]){
                    br[u][v] = br[v][u] = 1;
                }
                low[u] = min(low[u],low[v]);
                
            }else low[u] = min(low[u],num[v]);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    cin>>n>>m;
    for(int i=1,u,v;i<=m;++i){
        cin>>u>>v;
        g[u][v]=g[v][u]=1;
    }
    
    h[1]=1;
    dfs(1);
    
    cin>>q;
    while(q--){
        int type,a,b,c,g1,g2;
        cin>>type;
        if(type==1){
            cin>>a>>b>>g1>>g2;
            if(solve1(a, b, g1, g2)) cout << "yes\n";
            else cout << "no\n";
        }else{
            cin>>a>>b>>c;
            if(solve2(a,b,c)) cout << "yes\n";
            else cout << "no\n";
        }
    }
    return 0;
}
