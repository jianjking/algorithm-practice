#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class FindSumPairs {
public:
    unordered_map<int, int>map1;
    unordered_map<int, int>map2;
    vector<int>arr1;
    vector<int>arr2;
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        map1.clear();
        map2.clear();
        for (auto& p : nums1)map1[p]++;
        for (auto& p:nums2)map2[p]++;
        arr1 = nums1;
        arr2 = nums2;
    }

    void add(int index, int val) {
        map2[arr2[index]]--;
        arr2[index] += val;
        map2[arr2[index]]++;
    }

    int count(int tot) {
        int ans = 0;
        for (auto& p : map2) {
            if (map1.find(tot - p.first) != map1.end())ans += p.second * map1[tot - p.first];
        }
        return ans;
    }
};
