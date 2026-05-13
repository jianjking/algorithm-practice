#include<iostream>
#include<vector>
using namespace std;
int f(vector<vector<vector<int>>>& dp,vector<int>&nums,vector<vector<int>>&graph,int i, int j, int k) {
	if (k == 0)return 0;
	if (k == 1 || j == 0)return nums[i];
	if (dp[i][j][k] != -1)return dp[i][j][k];
	int ans = f(dp,nums,graph,i, j - 1, k);
	int v = graph[i][j - 1];
	for (int s = 1; s < k; s++) {
		ans = max(ans, f(dp, nums, graph,i, j - 1, k - s) + f(dp, nums, graph,v, graph[v].size(), s));
	}
	dp[i][j][k] = ans;
	return ans;
}
int main() {
	int n, limit;
	cin >> n >> limit;
	limit++;
	vector<int>nums(n + 1);
	nums[0] = 0;
	vector<vector<int>>graph(n + 1);
	for (int i = 1;i <= n;i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(i);
		nums[i] = b;
	}
	vector<vector<vector<int>>>dp(n + 1, vector<vector<int>>(0));
	for (int i = 0;i <= n;i++) {
		dp[i].resize(graph[i].size() + 1, vector<int>(limit+ 1, -1));
	}
	cout << f(dp, nums,graph,0, graph[0].size(), limit)<< endl;
}
//#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 301;

int nums[MAXN];         // 每门课程的学分
int head[MAXN];         // 邻接表头指针
int nextEdge[MAXN];     // 邻接表下一条边
int to[MAXN];           // 邻接表目标节点
int edgeCnt;            // 当前边的编号

int dfnCnt;             // dfn 序号计数器
int val[MAXN + 1];      // dfn序对应的课程学分
int size1[MAXN + 1];     // 以当前 dfn 序为根的子树大小
int dp[MAXN + 2][MAXN]; // 动态规划数组

int n, m;

void build(int n, int m) {
    edgeCnt = 1;
    dfnCnt = 0;
    memset(head, 0, sizeof(head));
    memset(dp, 0, sizeof(dp));
}

void addEdge(int u, int v) {
    nextEdge[edgeCnt] = head[u];
    to[edgeCnt] = v;
    head[u] = edgeCnt++;
}

// 返回以 u 为根的子树大小，同时设置 dfn 序、val、size
int f(int u) {
    int i = ++dfnCnt;
    val[i] = nums[u];
    size1[i] = 1;
    for (int ei = head[u]; ei > 0; ei = nextEdge[ei]) {
        int v = to[ei];
        size1[i] += f(v);
    }
    return size1[i];
}

int compute() {
    f(0); // 从虚拟根节点0开始DFS建立dfn序、size、val

    // 从后往前跑背包
    for (int i = n + 1; i >= 2; i--) {
        for (int j = 1; j <= m; j++) {
            // 不选当前课程，跳过当前整棵子树
            dp[i][j] = max(dp[i][j], dp[i + size1[i]][j]);
            // 选当前课程，必须要选 1 个节点，+ val[i]
            if (j - 1 >= 0) {
                dp[i][j] = max(dp[i][j], val[i] + dp[i + 1][j - 1]);
            }
        }
    }
    return nums[0] + dp[2][m]; // 返回包含虚拟根0 + 真实子结构的最大值
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m) {
        build(n, m);
        for (int i = 1; i <= n; i++) {
            int pre, score;
            cin >> pre >> score;
            addEdge(pre, i);
            nums[i] = score;
        }
        nums[0] = 0; // 虚拟根节点初始值为0
        cout << compute() << '\n';
    }
    return 0;
}
