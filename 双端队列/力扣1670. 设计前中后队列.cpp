#include<iostream>
#include<vector>
using namespace std;
class FrontMiddleBackQueue {
    deque<int> L, R;
public:
    FrontMiddleBackQueue() {}

    void pushFront(int val) {
        L.push_front(val);
        balance();
    }
    void pushMiddle(int val) {
        if (L.size() > R.size()) {
            R.push_front(L.back());
            L.pop_back();
        }
        L.push_back(val);
        balance();
    }
    void pushBack(int val) {
        R.push_back(val);
        balance();
    }
    int popFront() {
        if (L.empty() && R.empty()) return -1;
        int x = L.empty() ? R.front() : L.front();
        if (L.empty()) R.pop_front();
        else L.pop_front();
        balance();
        return x;
    }
    int popMiddle() {
        if (L.empty() && R.empty()) return -1;
        int x = (L.size() == R.size() ? L.back() : L.back());
        L.pop_back();
        balance();
        return x;
    }
    int popBack() {
        if (L.empty() && R.empty()) return -1;
        if (R.empty()) {
            int x = L.back(); L.pop_back();
            balance();
            return x;
        }
        int x = R.back(); R.pop_back();
        balance();
        return x;
    }
private:
    void balance() {
        // ±£Ö¤ L.size() == R.size() »ò L.size() == R.size()+1
        if (L.size() > R.size() + 1) {
            R.push_front(L.back());
            L.pop_back();
        }
        if (L.size() < R.size()) {
            L.push_back(R.front());
            R.pop_front();
        }
    }
};
