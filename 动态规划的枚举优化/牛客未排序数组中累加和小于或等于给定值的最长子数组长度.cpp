#include<iostream>
#include<vector>
#include<climits>
using namespace std;
//因为前缀和如果后一个小于前一个没必要作为答案，因为k>=sums[i]-sums[j]
//sums[j]>=sums[i]-k;\
//前一个数如果比后一个数大那她一定会作为答案
int find1(vector<int>& target, int k, int i) {
    int r = i - 1;
    int l = 0;
    int ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (target[mid] >= k) {
            ans = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return ans;
}
int main() {
    int n, k;
    cin >> n >> k;
    vector<int>sums(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        sums[i] = sums[i - 1] + a;;
    }
    vector<int>target(sums);
    for (int i = 1; i <= n; i++) {
        if (target[i] < target[i - 1]) {
            target[i] = target[i - 1];
        }
    }
    int ans = INT_MIN;
    for (int i = 1; i <= n; i++) {
        int m = find1(target, sums[i] - k, i);
        if (m == -1)continue;
        ans = max(ans, i - m);
    }
    cout << ans << endl;
    return 0;
}