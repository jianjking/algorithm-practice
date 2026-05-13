#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct compare {
	bool operator()(int a, int b) {
		return a > b;
	}
};
int main() {
	int n;
	cin >> n;
	priority_queue<int, vector<int>, compare>heap;
	for (int i = 0;i < n;i++) {
		int a;
		cin >> a;
		heap.push(a);
	}
	int ans = 0;
	while (!heap.empty()) {
		if (heap.size() == 1) {
			break;
		}
		 int a = heap.top();
		heap.pop();
		int b = heap.top();
		heap.pop();
		ans += a + b;
		heap.push(a + b);
	}
	cout<<ans<<endl;
}