#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<unordered_map>
using namespace std;
class MajorityChecker {
public:
    struct Node {
        int cand;
        int cnt;
    };

    int n;
    vector<Node> st;
    vector<int> arr;
    unordered_map<int, vector<int>> pos;

    MajorityChecker(vector<int>& input) {
        arr = input;
        n = arr.size();
        st.resize(4 * n);

        // 记录每个值出现的位置
        for (int i = 0; i < n; ++i) {
            pos[arr[i]].push_back(i);
        }
        build(1, 0, n - 1);
    }

    // Boyer-Moore 合并
    Node merge(const Node& A, const Node& B) {
        if (A.cand == B.cand)
            return { A.cand, A.cnt + B.cnt };
        if (A.cnt > B.cnt)
            return { A.cand, A.cnt - B.cnt };
        return { B.cand, B.cnt - A.cnt };
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            st[idx] = { arr[l], 1 };
            return;
        }
        int mid = (l + r) >> 1;
        build(idx * 2, l, mid);
        build(idx * 2 + 1, mid + 1, r);
        st[idx] = merge(st[idx * 2], st[idx * 2 + 1]);
    }

    Node queryST(int idx, int l, int r, int L, int R) {
        if (L <= l && r <= R) return st[idx];
        int mid = (l + r) >> 1;
        if (R <= mid) return queryST(idx * 2, l, mid, L, R);
        if (L > mid) return queryST(idx * 2 + 1, mid + 1, r, L, R);
        Node leftRes = queryST(idx * 2, l, mid, L, R);
        Node rightRes = queryST(idx * 2 + 1, mid + 1, r, L, R);
        return merge(leftRes, rightRes);
    }

    int query(int left, int right, int limit) {
        Node res = queryST(1, 0, n - 1, left, right);
        int cand = res.cand;
        // 二分统计真实出现次数
        auto& vec = pos[cand];
        int occ = upper_bound(vec.begin(), vec.end(), right)
            - lower_bound(vec.begin(), vec.end(), left);
        return occ >= limit ? cand : -1;
    }
};