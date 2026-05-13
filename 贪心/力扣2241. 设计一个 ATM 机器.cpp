#include<iostream>
#include<vector>
#include<map>;
using namespace std;
class ATM {
public:
    map<int, int> arr;
    long long sum;

    ATM() {
        arr.clear();
        sum = 0;
    }

    void deposit(vector<int> banknotesCount) {
        // 累加库存
        arr[20] += banknotesCount[0];
        arr[50] += banknotesCount[1];
        arr[100] += banknotesCount[2];
        arr[200] += banknotesCount[3];
        arr[500] += banknotesCount[4];
        // 更新总金额
        sum += 20LL * banknotesCount[0]
            + 50LL * banknotesCount[1]
            + 100LL * banknotesCount[2]
            + 200LL * banknotesCount[3]
            + 500LL * banknotesCount[4];
    }

    vector<int> withdraw(int amount) {
        // 先判断总金额是否足够
        if (amount > sum) return { -1 };

        int orig = amount;
        vector<int> denom = { 500, 200, 100, 50, 20 };
        vector<int> used(5, 0);

        // 按面额从大到小贪心
        for (int i = 0; i < denom.size(); ++i) {
            int d = denom[i];
            int cnt;
            if (amount >= d && arr[d] > 0) {
                cnt = min(amount / d, arr[d]);
                used[i] = cnt;

                amount -= cnt * d;
            }

        }
        // 如果凑不出恰好金额，就撤销
        if (amount != 0) return { -1 };

        // 真正更新库存和总金额
        for (int i = 0; i < denom.size(); ++i) {
            arr[denom[i]] -= used[i];
        }
        sum -= orig;

        // 返回 20、50、100、200、500 张数
        return { used[4], used[3], used[2], used[1], used[0] };
    }
};
