#include<iostream>
#include<vector>
using namespace std;
class Allocator {
public:
    vector<int>ans;
    int n;
    Allocator(int n) {
        ans.assign(n, 0);
        this->n = n;
    }

    int allocate(int size, int mID) {
        int l = 0;
        int sz = 0;
        for (int i = 0;i < n;i++) {
            if (ans[i] == 0) {
                if (sz == 0)l = i;
                sz++;
            }
            else {
                sz = 0;
            }
            if (sz >= size)break;
        }
        if (sz >= size) {
            for (int i = l;i < l + size;i++) {
                ans[i] = mID;
            }
        }
        else return -1;
    }

    int freeMemory(int mID) {
        int cnt = 0;
        for (int i = 0;i < n;i++) {
            if (ans[i] == mID) {
                cnt++;
                ans[i] = 0;
            }
        }
        return cnt;
    }
};