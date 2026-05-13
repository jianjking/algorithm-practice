#include<iostream>
#include<vector>
#include<stack>
using namespace std;
class StockSpanner {
public:
    // 每个元素保存 {price, span}
    stack<pair<int, int>> st;

    StockSpanner() {
        // 构造时啥也不用做
    }

    int next(int price) {
        int span = 1;
        // 弹出所有价格 ≤ 当前价的历史记录，并把它们的 span 累加到今天
        while (!st.empty() && st.top().first <= price) {
            span += st.top().second;
            st.pop();
        }
        // 把今天的价格和计算好的 span 存进去
        st.push({ price, span });
        return span;
    }
};
