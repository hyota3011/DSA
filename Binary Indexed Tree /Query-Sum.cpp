#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>

typedef long long ll;
using namespace std;
const int N = 1e5+3;
int n,q,t,k;

ll bit[N];
int a[N];
void update(int u, int v){
    while(u<=n){
        bit[u]+=v;
        u+=u&-u;
    }
}
ll get(int u){
    ll ans = 0;
    while(u){
        ans+=bit[u];
        u-=u&-u;
    }
    return ans;
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    cin>>n>>q;
    for(int i=1;i<=n;++i){ cin>>a[i]; update(i,a[i]);}
    while(q--){
        int i,u,v;
        cin>>i>>u>>v;
        if(i==1){
            update(u,v);
        }else{
            cout << get(v)-get(u-1)<<'\n';
        }
    }

    return 0;
}
