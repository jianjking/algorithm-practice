#include <iostream>
#include <vector>
using namespace std;

/*
  逻辑说明：
  - person[u]：初始化时，如果 u 是 special(有人物) 就置 1，其它为 0。
                dfs1 结束后，person[u] == u 子树（包括自己）里 special 的总数。
  - incost[u]：覆盖“以 u 为根的子树里所有 special”并最终回到 u 的最小花费（双向算边权）。
  - line1[u], line2[u]：在 u 子树里，向下能到达的两条“最长 special 路径”的长度 (计边权)。
                     num[u] 记录是哪条儿子贡献了第一长。
  - dfs1 从根 1 开始，往下搜，依次累加子树的 person、incost，并更新 line1/line2/num。
  - outer[u]：覆盖“u 子树外所有 special 并最终回到 u” 的最小花费。
  - outln[u]：从 u 往上（经过父亲）到离 u 最近的 special（一定在 u 子树外）的最远距离。
             仅在 u 子树外至少有一个 special 时才有意义，否则设为 0。
  最终对于每个 i，答案 = incost[i] + outer[i] - max(line1[i], outln[i]).

  已全部改用 long long。
*/

void dfs1(long long son, long long father,
    vector<long long>& line1, vector<long long>& line2, vector<long long>& num,
    vector<long long>& incost, vector<long long>& person,
    vector<vector<pair<long long, long long>>>& graph)
{
    for (auto& e : graph[son]) {
        long long nxt = e.first;
        long long w = e.second;
        if (nxt == father) continue;
        dfs1(nxt, son, line1, line2, num, incost, person, graph);

        // 累加子树里的 special 数量
        person[son] += person[nxt];

        // 如果 nxt 子树里有人物，才会产生“incost”与“最长向下路径”：
        if (person[nxt] > 0) {
            // 覆盖 nxt 子树的所有 special 并回到 nxt：已经在 incost[nxt]
            // 还要走 son<->nxt 这条边来回 2*w
            incost[son] += incost[nxt] + 2 * w;

            // candidate = 从 son 沿着 son->nxt 这条边，再往下到 nxt 子树最远 special 的距离
            long long cand = w + line1[nxt];
            if (cand > line1[son]) {
                line2[son] = line1[son];
                num[son] = nxt;
                line1[son] = cand;
            }
            else if (cand > line2[son]) {
                line2[son] = cand;
            }
        }
    }
}

void dfs2(long long son, long long father, long long w, long long k,
    vector<long long>& line1, vector<long long>& line2, vector<long long>& num,
    vector<long long>& incost, vector<long long>& person,
    vector<vector<pair<long long, long long>>>& graph,
    vector<long long>& outer, vector<long long>& outln)
{
    if (son != 1) {
        // 判断“son 子树外是否还有 special”
        if (k - person[son] == 0) {
            // 子树外没人
            outer[son] = 0;
            outln[son] = 0;
        }
        else {
            // 有 special 在 son 子树外
            if (person[son] > 0) {
                // son 子树里也有人 ⇒ incost[father] 包含了 (incost[son]+2*w)
                outer[son] = incost[father] - incost[son] + outer[father];
            }
            else {
                // son 子树里没人 ⇒ incost[father] 不含 son 那支
                outer[son] = incost[father] + outer[father] + 2 * w;
            }
            // 计算 outln[son]：从 son 往上到 “某个在子树外的 special” 的最远距离
            long long bestDown = (num[father] != son ? line1[father] : line2[father]);
            long long bestUp = outln[father];
            outln[son] = w + max(bestDown, bestUp);
        }
    }

    // 对所有儿子递归
    for (auto& e : graph[son]) {
        long long nxt = e.first;
        long long wt = e.second;
        if (nxt == father) continue;
        dfs2(nxt, son, wt, k,
            line1, line2, num, incost, person,
            graph, outer, outln);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;

    // 读树：邻接表储存 (neighbor, weight)
    vector<vector<pair<long long, long long>>> graph(n + 1);
    for (long long i = 1; i < n; i++) {
        long long a, b, v;
        cin >> a >> b >> v;
        graph[a].push_back({ b, v });
        graph[b].push_back({ a, v });
    }

    // 标记哪些节点是 special（一开始 person[i]=1）
    vector<long long> person(n + 1, 0);
    for (long long i = 0; i < k; i++) {
        long long a;
        cin >> a;
        person[a] = 1;
    }

    // line1/line2/num/incost 的初始化
    vector<long long> line1(n + 1, 0), line2(n + 1, 0), num(n + 1, 0), incost(n + 1, 0);

    // 第一次 DFS 填 person[i], incost[i], line1[i], line2[i], num[i]
    dfs1(1, 0, line1, line2, num, incost, person, graph);

    // outer[i]、outln[i] 初始化为 0
    vector<long long> outer(n + 1, 0), outln(n + 1, 0);

    // 第二次 DFS 计算 outer[i], outln[i]
    dfs2(1, 0, 0, k, line1, line2, num, incost, person, graph, outer, outln);

    // 最终输出：incost[i] + outer[i] - max(line1[i], outln[i])
    for (long long i = 1; i <= n; i++) {
        long long ans = incost[i] + outer[i] - max(line1[i], outln[i]);
        cout << ans << "\n";
    }

    return 0;
}
