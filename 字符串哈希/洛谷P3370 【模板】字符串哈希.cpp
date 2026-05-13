#include<iostream>
#include<vector>
#include<unordered_set>
#include<algorithm>
using namespace std;
//int main() {
//	int n;
//	cin >> n;
//	unordered_set<string>f;
//	for (int i = 0;i < n;i++) {
//		string s;cin >> s;
//		if (f.find(s) == f.end()) {
//			f.insert(s);
//		}
//	}
//	cout<<f.size()<<endl;
//}
int g(char a) {
	if (a >= '0' && a <= '9') {
		return a - '0' + 1;
	}
	else if (a >= 'a' && a <= 'z') {
		return a - 'a' + 11;
	}
	else return a - 'A' + 37;
}
int main() {
	int n;
	cin >> n;
	int base = 13;
	vector<int>arr(n);
	for (int i = 0;i < n;i++) {
		string s;
		cin >> s;
		unsigned long long sum = g(s[0]);
		for (int j = 1;j< s.size();j++) {
			sum = sum * base + g(s[j]);
		}
		arr[i] = sum;
	}
	sort(arr.begin(), arr.end());
	auto p=unique(arr.begin(), arr.end());
	arr.erase(p, arr.end());
	cout << arr.size();
}
