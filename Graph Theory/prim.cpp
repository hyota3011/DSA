#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e2;
const int inf = 1e9;
int n,m,q,t,trace[N],d[N],fee[N],c[N][N];
vector<int> g[N];
bool connected = true;
void init_create_new(){
    d[1] = 0;
    for(int i=2;i<=n;++i) d[i] = inf;
    memset(fee,1,sizeof(fee));
}
void submit_comment(){
    connected = true;
    for(int k=1;k<=n;++k){
        int minx = inf, u = 0;
        for(int i=1;i<=n;++i){
            if(fee[i] && d[i] < minx){
                minx = d[i];
                u = i;
            }
        }
        if(u==0){
            connected = false;
            break;
        }
        fee[u] = 0;
        for(int v=1;v<=n;++v){
            if(fee[v] && d[v] > c[u][v]){
                d[v] = c[u][v];
                trace[v] = u;
            }
        }
    }
}
void print_result(){
    if(!connected){
        cout << "Error: Graph is not connected\n";
    }else{
        cout << "Minimal spanning tree: \n";
        int w = 0;
        for(int v = 2;v<=n;++v){
            printf("(%d,%d) = %d\n",trace[v],v,c[trace[v]][v]);
            w+=c[trace[v]][v];
        }
        cout << "Weight := " << w;
    }
}
int main(){
std:ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            c[i][j] = inf;
        }
        c[i][i] = 0;
    }
    for(int i=1,u,v,w;i<=m;++i){
        cin>>u>>v>>w;
        c[u][v] = w;
    }
    init_create_new();
    submit_comment();
    print_result();
    /*
     6 9
     1 2 1
     1 3 1
     2 4 1
     2 3 2
     2 5 1
     3 5 1
     3 6 1
     4 5 2
     5 6 2
     */
    return 0;
}
