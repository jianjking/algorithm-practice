#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;
const long long limit = 1e15;
int main() {
	long long n;
	cin >> n;
	vector<long long>arr;
	arr.push_back(1);
	arr.push_back(2);
	long long a = arr[0] + arr[1];
	while (a <= n) {
		arr.push_back(a);
		int m = arr.size();
		a = arr[m - 1] + arr[m - 2];
	}
	long long mn = LLONG_MAX;
	while (n) {
		auto p = upper_bound(arr.begin(), arr.end(), n) - arr.begin();
		p--;
		mn = min(mn, arr[p]);
		n -= arr[p];
	}
	cout << mn << endl;
}