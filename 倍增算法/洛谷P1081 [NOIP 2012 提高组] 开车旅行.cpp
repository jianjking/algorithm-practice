#include <iostream>
#include <algorithm>
#include <cmath>
#include <cfloat>
using namespace std;

static const int MAXN = 100005;
static const int MAXP = 31;
int n;
long long nums[MAXN];
int lastn[MAXN], nxt[MAXN];
int to1[MAXN], to2_[MAXN];
long long dist1[MAXN], dist2[MAXN];
int stto[MAXN][MAXP];
long long stdist[MAXN][MAXP], stdista[MAXN][MAXP], stdistb[MAXN][MAXP];

void update_near(int i, int j) {
    if (j == 0) return;
    long long d = llabs(nums[i] - nums[j]);
    if (to1[i] == 0 || dist1[i] > d || (dist1[i] == d && nums[j] < nums[to1[i]])) {
        dist2[i] = dist1[i];
        to2_[i] = to1[i];
        to1[i] = j;
        dist1[i] = d;
    }
    else if (to2_[i] == 0 || dist2[i] > d || (dist2[i] == d && nums[j] < nums[to2_[i]])) {
        to2_[i] = j;
        dist2[i] = d;
    }
}

pair<long long, long long> travel_steps(int s, long long x) {
    long long a = 0, b = 0;
    for (int p = MAXP - 1; p >= 0; --p) {
        if (stto[s][p] && stdist[s][p] <= x) {
            x -= stdist[s][p];
            a += stdista[s][p];
            b += stdistb[s][p];
            s = stto[s][p];
        }
    }
    if (dist2[s] <= x) a += dist2[s];
    return { a,b };
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> nums[i];

    // prepare sorted linked list
    static pair<long long, int> tmp[MAXN];
    tmp[0] = { 0,0 };
    for (int i = 1; i <= n; ++i) tmp[i] = { nums[i], i };
    tmp[n + 1] = { 0,0 };
    sort(tmp + 1, tmp + 1 + n);
    for (int i = 1; i <= n; ++i) {
        int id = tmp[i].second;
        lastn[id] = tmp[i - 1].second;
        nxt[id] = tmp[i + 1].second;
    }

    // find to1, to2 and remove from list
    for (int i = 1; i <= n; ++i) {
        int a = lastn[i];
        int b = lastn[a];
        int c = nxt[i];
        int d = nxt[c];
        update_near(i, a);
        update_near(i, b);
        update_near(i, c);
        update_near(i, d);
        // delete i from list
        if (a) nxt[a] = c;
        if (c) lastn[c] = a;
    }

    // build doubling
    for (int i = 1; i <= n; ++i) {
        int mid = to2_[i];
        stto[i][0] = to1[mid];
        stdist[i][0] = dist2[i] + dist1[mid];
        stdista[i][0] = dist2[i];
        stdistb[i][0] = dist1[mid];
    }
    for (int p = 1; p < MAXP; ++p) {
        for (int i = 1; i <= n; ++i) {
            int t = stto[i][p - 1];
            stto[i][p] = t ? stto[t][p - 1] : 0;
            if (t) {
                stdist[i][p] = stdist[i][p - 1] + stdist[t][p - 1];
                stdista[i][p] = stdista[i][p - 1] + stdista[t][p - 1];
                stdistb[i][p] = stdistb[i][p - 1] + stdistb[t][p - 1];
            }
        }
    }

    long long x0;
    cin >> x0;
    int best_s = 1;
    double best_ratio = DBL_MAX;
    for (int i = 1; i < n; ++i) {
        auto [A, B] = travel_steps(i, x0);
        double ratio = B == 0 ? DBL_MAX : (double)A / B;
        if (ratio < best_ratio || (ratio == best_ratio && nums[i] > nums[best_s])) {
            best_ratio = ratio;
            best_s = i;
        }
    }
    cout << best_s << '\n';

    int m;
    cin >> m;
    while (m--) {
        int s;
        long long x;
        cin >> s >> x;
        auto [A, B] = travel_steps(s, x);
        cout << A << ' ' << B << '\n';
    }

    return 0;
}