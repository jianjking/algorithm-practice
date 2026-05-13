#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
	long long cnt(int d, long long num) {
		long long ans = 0;
		for (long long left, right = 1, tmp = num, cur;tmp != 0;tmp /= 10, right *= 10) {
			left = tmp / 10;
			if (d == 0)left--;
			cur = tmp % 10;
			ans += left * right;
			if (d < cur) {
				ans += right;
			}
			else if (d == cur)ans += (num % right) + 1;
		}
		return  ans;
	}
	int countDigitOne(int n) {
		return cnt(1, n);
	}
};