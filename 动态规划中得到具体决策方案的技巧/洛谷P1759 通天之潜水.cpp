#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;
vector<int>weight;
vector<int>force;
vector<int>value;
//∑«ø’º‰—πÀı∞Ê±æ
void f1(vector<vector<vector<int>>>& dp, vector<vector<vector<string>>>& path, int n, int lm, int lf) {
	for (int i = 1;i <= n;i++) {
		for (int j = 0;j <= lm;j++) {
			for (int z = 0;z <= lf;z++) {
				dp[i][j][z] = dp[i - 1][j][z];
				path[i][j][z] = path[i - 1][j][z];
				if (j >= weight[i - 1] && z >= force[i - 1]) {
					string s1 = path[i - 1][j - weight[i - 1]][z - force[i - 1]].empty() ? "" : " ";
					s1 += to_string(i);
					if (dp[i - 1][j - weight[i - 1]][z - force[i - 1]] + value[i - 1] > dp[i][j][z]) {
						path[i][j][z] = path[i - 1][j - weight[i - 1]][z - force[i - 1]] + s1;
						dp[i][j][z] = dp[i - 1][j - weight[i - 1]][z - force[i - 1]] + value[i - 1];
					}
					else if (dp[i - 1][j - weight[i - 1]][z - force[i - 1]] + value[i - 1] == dp[i][j][z]) {
						if (path[i][j][z] > path[i - 1][j - weight[i - 1]][z - force[i - 1]] + s1) {
							path[i][j][z] = path[i - 1][j - weight[i - 1]][z - force[i - 1]] + s1;
						}
					}
				}
			}
		}
	}
	cout << dp[n][lm][lf] << endl;
	cout << path[n][lm][lf] << endl;
}
//ø’º‰—πÀı∞Ê±æ
void f2(vector<vector<int>>& dp,vector<vector<string>>& path, int n, int lm, int lf) {
	for (int i = 0;i < n;i++) {
		for (int j = lm;j >= weight[i];j--) {
			for (int z = lf;z >= force[i];z--) {
				string s1 = path[j-weight[i]][z-force[i]].empty() ? "" : " ";
				s1 += to_string(i+1);
				if (dp[j][z] < dp[j - weight[i]][z - force[i]]+value[i]) {
					path[j][z] = path[j - weight[i]][z - force[i]] + s1;
					dp[j][z] = dp[j - weight[i]][z - force[i]] + value[i];
				}
				else if (dp[j][z] == dp[j - weight[i]][z - force[i]] + value[i]) {
					if (path[j - weight[i]][z - force[i]] + s1 < path[j][z]) {
						path[j][z] = path[j - weight[i]][z - force[i]] + s1;
					}
				}
			}
		}
	}
	cout << dp[lm][lf] << endl;
	cout << path[lm][lf] << endl;
}
int main() {
	int lm, lf, n;
	cin >> lm >> lf >> n;
	weight.resize(n);
	force.resize(n);
	value.resize(n);
	for (int i = 0;i < n;i++) {
		scanf("%d%d%d", &weight[i], &force[i], &value[i]);
	}
	//vector<vector<vector<int>>>dp(n + 1, vector<vector<int>>(lm + 1, vector<int>(lf + 1, 0)));
	//vector<vector<vector<string>>>path(n + 1, vector<vector<string>>(lm + 1, vector<string>(lf + 1, "")));
	//f1(dp, path, n, lm, lf);
	vector<vector<int>>dp(lm + 1, vector<int>(lf + 1, 0));
	vector<vector<string>>path(lm + 1, vector<string>(lf + 1, ""));
	f2(dp, path, n, lm, lf);
}