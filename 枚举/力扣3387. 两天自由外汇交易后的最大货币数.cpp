#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        auto calc_amount = [&](vector<vector<string>>& pairs, vector<double>& rates) {
            unordered_map<string, vector<pair<string, double>>> g;
            for (int i = 0; i < pairs.size(); i++) {
                auto& p = pairs[i];
                double r = rates[i];
                g[p[0]].emplace_back(p[1], r);
                g[p[1]].emplace_back(p[0], 1 / r);
            }

            unordered_map<string, double> amount;
            auto dfs = [&](this auto&& dfs, const string& x, double cur_amount) -> void {
                amount[x] = cur_amount;
                for (auto& [to, rate] : g[x]) {
                    // 每个节点只需递归一次（重复递归算出来的结果是一样的，因为题目保证汇率没有矛盾）
                    if (!amount.contains(to)) {
                        dfs(to, cur_amount * rate);
                    }
                }
                };
            dfs(initialCurrency, 1);
            return amount;
            };

        auto day1_amount = calc_amount(pairs1, rates1);
        auto day2_amount = calc_amount(pairs2, rates2);

        double ans = 0;
        for (auto& [x, a2] : day2_amount) {
            ans = max(ans, day1_amount[x] / a2);
        }
        return ans;
    }
};

