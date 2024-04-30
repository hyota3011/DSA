#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>

typedef long long ll;
using namespace std;
const int N = 1e5+3;
int n,q,t,k;
int a[N];

vector<ll> bit1(N), bit2(N);
void updatePoint(vector<ll>& b, int u, ll v) {
    int idx = u;
    while (idx <= n) {
        b[idx] += v;
        idx += (idx & (-idx));
    }
}

void updateRange(int l, int r, ll v) {
    updatePoint(bit1, l, (n - l + 1) * v);
    updatePoint(bit1, r + 1, -(n - r) * v);
    updatePoint(bit2, l, v);
    updatePoint(bit2, r + 1, -v);
}

ll getSumOnBIT(vector<ll>& b, int u) {
    int idx = u;
    ll ans = 0;
    while (idx > 0) {
        ans += b[idx];
        idx -= (idx & (-idx));
    }
    return ans;
}

ll prefixSum(int u) {
    return getSumOnBIT(bit1, u) - getSumOnBIT(bit2, u) * (n - u);
}

ll rangeSum(int l, int r) {
    return prefixSum(r) - prefixSum(l - 1);
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    a[0]=0;
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        //diff[i]=a[i]-a[i-1];??
        updateRange(i, i, a[i]);// the initial stat of bit is 0 at all (includes diff array of bit) so you just
        // need to update range with the value increased
    }
    while(q--){
        int i,u,v,x;
        cin>>i;
        if(i==1){
            cin>>u>>v>>x;
            updateRange(u,v,x);
        }else{
            cin>>u>>v;
            cout << rangeSum(u, v) <<'\n';
        }
    }
    
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Proccess returned 0 (0x0)\texecution time : "
    << ((chrono::duration<double>)(end - begin)).count()<< " s\n";
    
    return 0;
}
