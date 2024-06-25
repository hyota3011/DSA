#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;
typedef long long ll;

const int N = 1e2;
int n,m,lab[N];
bool connected = false;
struct Edge{
    int u,v,w;
    bool mark;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){mark=false;}
} xintv[N];
void swap(Edge *a,Edge *b){
    Edge tmp = *a;
    *a = *b;
    *b = tmp;
}
vector<pair<int,int>> g[N];
int get_root(int v){
    while(lab[v]>0) v=lab[v];
    return v;
}
void union_ducoh(int r1,int r2){
    int x = lab[r1] + lab[r2];
    if(lab[r1] > lab[r2]){
        lab[r1] = r2;
        lab[r2] = x;
    }else{
        lab[r2] = r1;
        lab[r1] = x;
    }
}
void heapify(Edge arr[], int n, int i){
    int idx = i, l = 2*i, r = 2*i+1;
    if (l <= n && arr[l].w < arr[idx].w) idx = l;
    if (r <= n && arr[r].w < arr[idx].w) idx = r;
    if (idx != i){
        swap(arr[i], arr[idx]);
        heapify(arr, n, idx);
    }
}

void kruskal(){
    int cnt = 0;
    //create heap
    for(int i=m>>1;i>=1;--i){
        heapify(xintv,m,i);
    }
    for(int i=m;i>=2;--i){
        swap(xintv[1],xintv[i]);
        heapify(xintv,i-1,1);
        
        int r1 = get_root(xintv[i].u);
        int r2 = get_root(xintv[i].v);
        if(r1!=r2){
            xintv[i].mark=true;
            ++cnt;
            if(cnt==n-1){
                connected = true;
                return void();
            }
            union_ducoh(r1,r2);
        }
    }
}
void init_view_detail(){
    if(connected){
        cout << "Minimal spanning tree: \n";
        int cnt = 0;
        int w = 0;
        for(int i=1;i<=m;++i){
            if(xintv[i].mark){
                printf("(%d,%d) = %d\n",xintv[i].u,xintv[i].v,xintv[i].w);
                ++cnt;
                w+=xintv[i].w;
            }
            if(cnt == n-1) break;
        }
        cout << "Weight = " << w << endl;
    }else{
        cout << "Not connected\n";
    }
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    cin>>n>>m;
    for(int i=1,u,v,w;i<=m;++i){
        cin>>u>>v>>w;
        xintv[i] = {u,v,w};
        g[u].push_back({v,w});
    }
    memset(lab,-1,sizeof(lab));
    kruskal();
    init_view_detail();
    
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
