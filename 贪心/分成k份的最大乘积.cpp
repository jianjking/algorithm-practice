#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;
long long f3(int a, int b) {
	long long x = a;
	long long ans = 1;
	while (b) {
		if (b & 1) {
			ans = (x * ans) ;
		}
		x *= x;
		b >>= 1;
	}
	return ans;
}
long long f1(int n, int k) {
	int a = n / k;
	int b = n%k;
	long long c = f3(a + 1, b);
	long long d = f3(a, k - b);
	return c * d;
}
long long f(int n, int k) {
	if (k == 1)return n;
	long long ans = 0;
	for (int i = 1;i <=1+ n-k;i++) {
		ans=max(ans,i*f(n - i, k - 1));
	}
	return ans;
}
long long f2(int n, int k) {
	return f(n, k);
}
int main() {
	srand(time(0));
	int timelimit = 2000;
	for (int i = 1;i <= timelimit;i++) {
		int n =rand()%20+1;
		int k = rand()%n+1;
		long long ans1 = f1(n, k);
		long long ans2 = f2(n, k);
		if (ans1 != ans2) {
			cout << "出错了" << endl;
		}
		if (i % 100 == 0) {
			cout << "第" << i << "组测验已结束"<<endl;
		}
	}

}