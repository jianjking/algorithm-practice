#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<set>
#include<unordered_map>
using namespace std;
bool finish(vector<int>& num, set<int>& cnt) {
	int n = num.size();
	for (int i = 0;i < n;i++) {
		for (int j = i + 1;j < n;j++) {
			int d = abs(num[i] - num[j]);
			if (cnt.find(d) == cnt.end()) {
				num.push_back(d);
				cnt.insert(d);
			}
		}
	}
	return n == num.size();
}
int f1(vector<int>& arr) {
	int n = arr.size();
	vector<int>num(arr.begin(),arr.end());
	set<int>cnt;
	for (auto& p : arr) {
		cnt.insert(p);
	}
	while (!finish(num, cnt)) {

	}
	return num.size();
	
}
int gcd(int a, int b) {
	return b != 0 ? gcd(b, a % b) : a;
}
int f2(vector<int>& arr) {
	int max_val = 0;
	int gcd_val = 0;
	for (int num : arr) {
		max_val = max(max_val, num);
		if (num != 0) {
			gcd_val = gcd_val == 0 ? num : gcd(gcd_val, num);
		}
	}
	if (gcd_val == 0) {
		return arr.size();
	}
	int ans = max_val / gcd_val ;
	unordered_map<int, int> cnts;
	for (int num : arr) {
		cnts[num]++;
	}
	for (auto& p : arr) {
		if (!cnts.count(0)&&cnts[p] > 1) {
			ans++;
			break;
		}
	}
	for (auto& p: cnts) {
		if (p.first!= 0) {
			ans += p.second - 1;
		}
	}

	if (cnts.count(0) && cnts[0] >= 1) {
		ans += cnts[0];
	}

	return ans;
}
int main() {
	srand(time(0));
	for (int i = 0;i < 20000;i++) {
		int n = rand() % 20 + 1;
		vector<int>arr(n);
		for (int j = 0;j < n;j++) {
			arr[j] = rand() % 100;
		}
		int len1 = f1(arr);
		int len2 = f2(arr);
		if (len1 != len2)cout << "出错了" << endl;
		if (i % 100 == 0)cout << "第" << i << "组测试完成" << endl;
	}
	return 0;
}