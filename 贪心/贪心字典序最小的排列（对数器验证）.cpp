#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<algorithm>
using namespace std;
string create(int m, int v) {
	int len = rand() % m + 1;
	string s;
	for (int i = 0;i < len;i++) {
		s +=(char)( 'a' + rand() % v + 1);
	}
	return s;
}
void f3(vector<string>& str, int i, vector<string>& ans) {
	if (i == str.size()) {
		string s1;
		for (auto& p : str) {
			s1 += p;
		}
		ans.push_back(s1);
	}
	else {
		for (int j = i;j < str.size();j++) {
			swap(str[i], str[j]);
			f3(str, i + 1, ans);
			swap(str[i], str[j]);
		}
	}
}
string f2(vector<string>& s) {
	sort(s.begin(), s.end(), [](string& a, string& b) {
		return a + b < b + a;
		});
	string result;
	for (auto& p : s) {
		result += p;
	}
	return result;
}
string f1(vector<string>& s) {
	vector<string>ans;
	f3(s, 0, ans);
	sort(ans.begin(), ans.end());
	return ans[0];
}
void test() {
	int n = 8;
	int m = 7;
	int v = 3;
	int timelimit = 2000;
	for (int i = 0;i < timelimit;i++) {
		int size = rand() % n + 1;
		vector<string>s(size);
		for (int i = 0;i < size;i++) {
			s[i] = create(m, v);
		}
		string s1 = f1(s);
		string s2 = f2(s);
		if (s1 != s2) {
			cout << "出错了" << endl;
		}
		if (i % 100 == 0) {
			cout << "第" << i << "组试验结束"<<endl;
		}
	}
}
int main() {
	srand(time(0));
	test();
}