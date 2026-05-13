#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main() {
	int n;
	cin >> n;
	vector<int>a1(n + 1);
	vector<int>a2(n + 1);
	vector<int>where(n + 1);
	for (int i = 1;i <= n;i++) {
		scanf("%d", &a1[i]);
		where[a1[i]] = i;
	}
	vector<int>num;
	for (int i = 1;i <= n;i++) {
		scanf("%d", &a2[i]);
	}
	for (int i = 1;i <= n;i++) {
		auto pos = lower_bound(num.begin(), num.end(), where[a2[i]]) - num.begin();
		if (pos == num.size()) {
			num.push_back(where[a2[i]]);
		}
		else {
			num[pos] = where[a2[i]];
		}
	}
	cout << num.size() << endl;
}