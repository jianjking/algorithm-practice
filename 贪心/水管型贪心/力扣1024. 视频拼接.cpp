#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        // maxn[i] 表示所有以 i 为起点的片段中，能延伸到的最远终点
        vector<int> maxn(time);
        // last：在当前已考察过的起点 ≤ i 中，最远能到达的位置
        // pre：上一次接入的视频片段的终点
        // ret：已接入的视频片段数量
        int last = 0, ret = 0, pre = 0;

        // 预处理：统计每个起点能到的最远终点
        for (auto& it : clips) {
            int start = it[0], end = it[1];
            if (start < time) {
                maxn[start] = max(maxn[start], end);
            }
        }

        // 线性扫描 [0, time)
        for (int i = 0; i < time; i++) {
            // 更新当前可达最远终点
            last = max(last, maxn[i]);

            // 如果 i == last，说明到 i 时所有片段都达不到更远位置，覆盖失败
            if (i == last) {
                return -1;
            }

            // 当扫描到上一次接入片段的终点时，需要新接入一段片段
            if (i == pre) {
                ret++;        // 接入一段
                pre = last;   // 将“已接入终点”更新为目前能到的最远位置
            }
        }

        return ret;  // 返回最少接入片段数
    }
};
