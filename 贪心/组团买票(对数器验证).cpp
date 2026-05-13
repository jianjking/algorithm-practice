#include<iostream>
#include<vector>
#include<set>
#include<ctime>
#include<cstdlib>
#include<queue>
using namespace std;


int dfs_brute(int idx, int n, const vector<pair<int, int>>& games, vector<int>& cnts) {
    if (idx == n) {
        int total = 0;
        for (int j = 0; j < (int)games.size(); j++) {
            int k = games[j].first;
            int b = games[j].second;
            int x = cnts[j];
            total += max((b - k * x) * x, 0);
        }
        return total;
    }
    // 选不参与任何项目
    int best = dfs_brute(idx + 1, n, games, cnts);
    // 或者参与某个项目 j
    for (int j = 0; j < (int)games.size(); j++) {
        cnts[j]++;
        best = max(best, dfs_brute(idx + 1, n, games, cnts));
        cnts[j]--;
    }
    return best;
}

int brute(vector<pair<int, int>>& games, int n) {
    vector<int> cnts(games.size(), 0);
    return dfs_brute(0, n, games, cnts);
}
struct Game {
    int k, b, people;
    Game(int _k, int _b) : k(_k), b(_b), people(0) {}
    int earn() const {
        int cur = max((b - k * people) * people, 0);
        int nxt = max((b - k * (people + 1)) * (people + 1), 0);
        return nxt - cur;
    }
};

int greedy(vector<pair<int, int>>& games, int n) {
    vector<unique_ptr<Game>> pool;
    pool.reserve(games.size());
    auto cmp = [](Game* a, Game* b) { return a->earn() < b->earn(); };
    priority_queue<Game*, vector<Game*>, decltype(cmp)> heap(cmp);

    for (auto& g : games) {
        pool.emplace_back(make_unique<Game>(g.first, g.second));
        heap.push(pool.back().get());
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        Game* top = heap.top();
        int delta = top->earn();
        if (delta <= 0) break;  
        heap.pop();
        ans += delta;
        top->people++;
        heap.push(top);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand((unsigned)time(nullptr));
    const int TESTS = 2000;
    cout << "测试开始\n";
    for (int t = 1; t <= TESTS; t++) {
        int m = rand() % 6 + 1;
        int n = rand() % 5 + 1;
        vector<pair<int, int>> games(m);
        for (int i = 0; i < m; i++) {
            games[i].first = rand() % 10 + 1;   
            games[i].second = rand() % 200 + 1;  
        }
        auto games_copy = games;
        int ans_greedy = greedy(games, n);
        int ans_brute = brute(games_copy, n);
        if (ans_greedy != ans_brute) {
            cout << "出错了! greedy=" << ans_greedy
                << ", brute=" << ans_brute << "\n";
            return 0;
        }
        if (t % 100 == 0) {
            cout << "第 " << t << " 组测试完成\n";
        }
    }
    cout << "测试结束\n";
    return 0;
}
