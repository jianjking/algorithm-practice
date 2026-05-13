#include <bits/stdc++.h>
using namespace std;

long long gcdll(long long a, long long b){
    return b==0 ? a : gcdll(b, a%b);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    long long n,q;
    cin>>n>>q;
    vector<long long> v(n), c(n); // v=体积, c=价值（按题面）
    double mx = -DBL_MAX;
    long long mxnum = 0;

    for(long long i=0;i<n;i++){
        cin>>v[i]>>c[i];                // 读入：体积 v[i]，价值 c[i]
        double dens = (double)c[i]/(double)v[i]; // 按价值/体积选密度最大
        if(dens > mx){
            mx = dens;
            mxnum = i;
        }
    }

    const long long M = v[mxnum]; // 以密度最大物品的体积为模
    vector<long long> dp((size_t)M, LLONG_MIN);
    dp[0] = 0;

    for(long long i=0;i<n;i++){
        if(i==mxnum) continue;
        long long g = gcdll(M, v[i]);
        for(long long j=0;j<g;j++){
            for(long long z=j%M, cnt=0; cnt<=2; z=(z+v[i])%M){
                if(dp[z]==LLONG_MIN) { if(z==j) cnt++; continue; }
                long long nz = (z + v[i]) % M;
                long long dec = ((z + v[i]) / M) * c[mxnum]; // 跨过多少个 M，就扣多少份基准价值
                dp[nz] = max(dp[nz], dp[z] + c[i] - dec);
                if(z==j) cnt++;
            }
        }
    }

    while(q--){
        long long V; cin>>V;            // 询问体积
        long long r = V % M;
        if(dp[r]==LLONG_MIN) cout << "-1\n";
        else cout << dp[r] + (V/M) * c[mxnum] << '\n';
    }
}
