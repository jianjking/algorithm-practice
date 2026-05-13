#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void add(long long a, long long b, vector<long long>& tree) {
    long long n = tree.size();
    while (a < n) {
        tree[a] += b;
        a += a & (-a);
    }
}

long long queriry(long long a, const vector<long long>& tree) {
    long long sum = 0;
    while (a > 0) {
        sum += tree[a];
        a -= (a & -a);
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> num(n);
    vector<long long> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }

    nums = num;
    sort(nums.begin(), nums.end());
    auto p1 = unique(nums.begin(), nums.end());
    nums.erase(p1, nums.end());

    long long m = nums.size();
    vector<long long> tree1(m + 1, 0);
    vector<long long> tree2(m + 1, 0);

    for (int i = 0; i < n; i++) {
        num[i] = lower_bound(nums.begin(), nums.end(), num[i]) - nums.begin() + 1;
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += queriry(num[i] - 1, tree2);
        add(num[i], 1, tree1);
        add(num[i], queriry(num[i] - 1, tree1), tree2);
    }

    cout << ans << "\n";
    return 0;
}