#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;
typedef long long ll;

const int N = 1e2;
int n,m,trace[N],par[N];
bool connected = false;
struct Edge{
    int u,v,w;
    bool mark;
    Edge(int _u=0,int _v=0,int _w=0):u(_u),v(_v),w(_w){mark=false;}
    static void swap(Edge &a,Edge &b){
        Edge tmp = a;
        a=b;
        b=tmp;
    }
}g[N];

class Heap{
public:
    static void heapify(Edge arr[], int i, int n){
        int idx = i,l=i<<1,r=i<<1|1;
        if(l<=n&&arr[l].w<arr[idx].w)idx=l;
        if(r<=n&&arr[r].w<arr[idx].w)idx=r;
        if(idx!=i){
            Edge::swap(arr[idx],arr[i]);
            heapify(arr,idx,n);
        }
    }
};
class Kruskal{
public:
    int get_root(int u){
        while(par[u]>0) u = par[u];
        return u;
    }
    void union_tree(int u,int v){
        u = get_root(u);
        v = get_root(v);
        if(u!=v){
            int sum = par[u] + par[v];
            if(par[u] > par[v]){
                par[u] = v;
                par[v] = sum;
            }else{
                par[v] = u;
                par[u] = sum;
            }
        }
    }
    void main(Edge arr[],int m,int n){
        int cnt = 0;
        for(int i=m>>1;i>=1;--i) Heap::heapify(g,i,m);
        for(int i=m;i>1;--i){
            Edge::swap(arr[1],arr[i]);
            Heap::heapify(g,1,i-1);
            
            Edge &last = arr[i];
            int r1 = get_root(last.u), r2 = get_root(last.v);
            if(r1!=r2){
                last.mark=true;
                ++cnt;
                if(cnt == n-1){
                    connected = true;
                    return void();
                }
                union_tree(r1, r2);
            }
            
        }
    }
    void print_result(){
        if(connected){
            cout << "Minimal spanning tree: \n";
            int cnt = 0;
            int w = 0;
            for(int i=1;i<=m;++i){
                if(g[i].mark){
                    printf("(%d,%d) = %d\n",g[i].u,g[i].v,g[i].w);
                    ++cnt;
                    w+=g[i].w;
                }
                if(cnt == n-1) break;
            }
            cout << "Weight = " << w << endl;
        }else{
            cout << "Not connected\n";
        }
    }
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    cin>>n>>m;
    for(int i=1,u,v,w;i<=m;++i){
        cin>>u>>v>>w;
        g[i] = {u,v,w};
    }
    memset(par,-1,sizeof(par));
    Kruskal ks;
    ks.main(g, m, n);
    ks.print_result();
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
