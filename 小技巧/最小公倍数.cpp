#include<iostream>
using namespace std;
long gcd(long a, long b) {
	return b == 0 ? a : gcd(b, a % b);
}
long lcm(long  a,long b) {
	return a / gcd(a, b) * b;
}
int main() {
	int a, b;
	cin >> a >> b;
	cout << lcm(a, b) << endl;
}
