#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
constexpr int N = 4e5+10;

int n,m,q,en[N],tour[N],par[N],st[N],bit[N],c[N];
vector<int> g[N];

struct Node{
    ll val;
    ll lazy;
    Node():val(0),lazy(0){}
    
} t[N<<2];
void fix(int id,int l,int r){
    if(t[id].lazy==0) return;
    ll val = t[id].lazy;
    t[id].val = 1ll<<val;
    if(l!=r){
        t[id<<1].lazy = val;
        t[id<<1|1].lazy = val;
    }
    t[id].lazy = 0;
}
void update(int id,int l,int r,int u,int v,int val){
    fix(id,l,r);
    if(l > v || r < u){
        return;
    }
    if(l>=u && r<=v){
        t[id].lazy = val;
        fix(id,l,r);
        return;
    }
    int mid = (l+r)>>1;
    update(2*id,l,mid,u,v,val);
    update(2*id+1,mid+1,r,u,v,val);
    t[id].val = t[id<<1].val | t[id<<1|1].val;
}
ll get(int id,int l,int r,int u,int v){
    fix(id,l,r);
    if(l > v || r < u){
        return 0;
    }
    if(l>=u && r<=v){
        return t[id].val;
    }
    int mid = (l+r)>>1;
    ll g1 = get(2*id,l,mid,u,v);
    ll g2 = get(2*id+1,mid+1,r,u,v);
    return g1 | g2;
}
void dfs(int u){
    tour[++m] = u;
    st[u] = m;
    for(int v : g[u]){
        if(v!=par[u]){
            par[v]=u;
            dfs(v);
        }
    }
    en[u] = m;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>c[i];
    }
    for(int i=1,u,v;i<=n-1;++i){
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    m=0;
    par[1]=1;
    dfs(1);
    //Euler tour
    //1 2 3 2 4 2 1 5 1
    //st[u] ... en[u]
    for(int i=1;i<=n;++i){
        update(1,1,n,st[i],st[i],c[i]);
    }
    while(q--){
        int t,v,c1;
        cin>>t>>v;
        if(t==1){
            cin>>c1;
            update(1,1,n,st[v],en[v],c1);
        }else{
            cout << __builtin_popcountll(get(1,1,n,st[v],en[v])) << '\n';
        }
    }
    return 0;
}
