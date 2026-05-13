#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
	int countPrimes(int n) {
		n--;
		int ans = 0;
		if (n <= 2)return n == 2;
		vector<bool>visit(n + 1);
		for (int i = 2;i * i <= n;i++) {
			for (int j = i * i;j <= n;j += i) {
				visit[j] = true;
			}
		}
		for (int i = 2;i <= n;i++) {
			if (!visit[i]) {

				ans++;
			}
		}
		return ans;
	}
};