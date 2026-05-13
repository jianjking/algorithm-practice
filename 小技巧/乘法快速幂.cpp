#include<iostream>
#include<vector>
using namespace std;
// a=3,b=5 b的二进制是 0101
//也就是说 a的一次方 ×a的四次方
long long mi(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b & 1)res = res * a;
		a *= a;
		b >>= 1;
	}
	return res;
}
int main() {
	long long a, b;
	cin >> a >> b;
	cout<<mi(a, b)<<endl;
}