#include<iostream>
#include<vector>
using namespace std;
int main() {
	int n;
	cin >> n;
	vector<bool>visit(n + 1);
	vector<int>arr((n + 1) / 2);
	int cnt = 0;
	for (int i = 2;i<= n;i++) {
		if (!visit[i]) {
			arr[cnt++] = i;
		}
			for (int j = 0;j < cnt;j++) {
				if (arr[j] * i > n)break;
				visit[arr[j] * i] = true;
				if (i % arr[j] == 0)break;

			}
		
	}
	cout << cnt << endl;
}
